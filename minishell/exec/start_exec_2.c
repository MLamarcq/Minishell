/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:33:14 by mael              #+#    #+#             */
/*   Updated: 2023/04/28 12:13:17 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

int	init_sep_type(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	int		i;

	tmp = mini_sh->rl_out_head;
	if (mini_sh->sep_type)
	{
		free(mini_sh->sep_type);
		mini_sh->sep_type = NULL;
	}
	if (mini_sh->redir_alone && mini_sh->redir_alone == SUCCESS)
		mini_sh->sep_type = (int *)malloc(sizeof(int) * (2));
	else
	{
		mini_sh->sep_type = (int *)malloc(sizeof(int) * (mini_sh->sep_2 + 1));
	}
	if (!mini_sh->sep_type)
		return (FAIL_MALLOC);
	i = 0;
	// if (is_sep(tmp->word) == SUCCESS)
	// 	tmp = tmp->next;
	while (tmp)
	{
		if (is_sep(tmp->word) == SUCCESS && tmp->type && i < mini_sh->sep_2)
		{
			mini_sh->sep_type[i] = tmp->type;
			i++;
		}
		tmp = tmp->next;
	}
	mini_sh->sep_type[i] = FAIL;
	mini_sh->sep_id = 0;
	return (SUCCESS);
}

void	print_cmd_not_found(t_mini_sh *mini_sh, int i_exec)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(mini_sh->prepare_exec[i_exec][0], 2);
	ft_putstr_fd(": command not found\n", 2);
	close_all(mini_sh);
	free_all(mini_sh);
	exit (127);
}

void	exec_cmd(t_mini_sh *mini_sh, int i_exec)
{
	char	*cmd_abs_path;

	cmd_abs_path = NULL;
	if (access(mini_sh->prepare_exec[i_exec][0], X_OK) == 0)
		execve(mini_sh->prepare_exec[i_exec][0], \
		mini_sh->prepare_exec[i_exec], mini_sh->env);
	cmd_abs_path = ft_find_path_2(mini_sh, mini_sh->prepare_exec[i_exec][0]);
	if (cmd_abs_path != NULL)
	{
		free(mini_sh->prepare_exec[i_exec][0]);
		mini_sh->prepare_exec[i_exec][0] = cmd_abs_path;
		execve(cmd_abs_path, mini_sh->prepare_exec[i_exec], mini_sh->env);
	}
	else
	{
		if ( i_exec > 0 && mini_sh->sep_type && mini_sh->sep_type[i_exec - 1] && mini_sh->sep_type[i_exec - 1] != PIPE)
		{
			g_exit_stt = 0;
			close_all(mini_sh);
			free_all(mini_sh);
			exit (0);
		}
		// if (i_exec > 0 && mini_sh->sep_type && mini_sh->sep_type[i_exec - 1] && mini_sh->sep_type[i_exec - 1] != PIPE)
		// 	return ;
		// else if (i_exec == 0 && mini_sh->sep_type && mini_sh->sep_type[i_exec] != PIPE)
		else if (i_exec == 0 && is_there_a_redir(mini_sh) == SUCCESS)
		{
			g_exit_stt = 0;
			close_all(mini_sh);
			free_all(mini_sh);
			exit (0);
		}
		else
		{
			// printf("minishell:%s: command not found\n",
			// mini_sh->prepare_exec[i_exec][0]);
			// ft_putstr_fd("command not found\n", 2);
			// free_all(mini_sh);
			// exit (127);
			print_cmd_not_found(mini_sh, i_exec);
		}
	}
}

int	init_tab_fd(t_mini_sh *mini_sh)
{
	int		i_init_fd;
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	i_init_fd = 0;
	//free_tab_fd(mini_sh);
	mini_sh->exec->tab_fd = NULL;
	mini_sh->exec->tab_fd = malloc(sizeof(int *) * (mini_sh->sep_2 + 1));
	if (!mini_sh->exec->tab_fd)
		return (FAIL_MALLOC);
	mini_sh->exec->tab_fd[mini_sh->sep_2] = 0;
	while (tmp)
	{
		if (!tmp)
			break ;
		while (tmp && is_sep_int(tmp->type) == FAIL)
			tmp = tmp->next;
		if (!tmp)
			break ;
		mini_sh->exec->tab_fd[i_init_fd] = malloc(sizeof(int) * 3);
		mini_sh->exec->tab_fd[i_init_fd][2] = 0;
		if (pipe(mini_sh->exec->tab_fd[i_init_fd]) == -1)
			return (printf(BACK_RED"pipe not working"RST"\n"), FAIL);
		if (tmp && tmp->type == PIPE && is_sep_int(tmp->next->type) == SUCCESS)
		{
			close(mini_sh->exec->tab_fd[i_init_fd][0]);
			mini_sh->exec->tab_fd[i_init_fd][0] = 0;
			tmp = tmp->next;
		}
		if (tmp)
			count_redir_for_alloc(tmp, mini_sh);
		i_init_fd++;
		tmp = tmp->next;
	}
	init_redir_fd(mini_sh);
	return (SUCCESS);
	(void)i_init_fd;
}

int	exec_builtin(t_mini_sh *mini_sh, int i)
{
	if (mini_sh->len_prepare_exec == 1)
	{
		if (do_built_in(mini_sh, i) == FAIL)
			return (FAIL);
		else
		{
			//exit(1);
			return (SUCCESS);
		}
	}
	return (FAIL);
}


int	exec_redir(t_mini_sh *mini_sh, int i_exec)
{
	if (i_exec < mini_sh->sep_2 && mini_sh->sep_type && mini_sh->sep_type[i_exec] != FAIL && mini_sh->sep_type[i_exec] == REDIR_R)
		do_redir_r(mini_sh, i_exec);
	else if (i_exec < mini_sh->sep_2 && mini_sh->sep_type && mini_sh->sep_type[i_exec] != FAIL && mini_sh->sep_type[i_exec] == APPEND)
		do_append(mini_sh, i_exec);
	else if (i_exec < mini_sh->sep_2 && mini_sh->sep_type && mini_sh->sep_type[i_exec] != FAIL && mini_sh->sep_type[i_exec] == HR_DOC)
		do_heredoc_redir(mini_sh, i_exec);
	else if (i_exec < mini_sh->sep_2 && mini_sh->sep_type && mini_sh->sep_type[i_exec] != FAIL && mini_sh->sep_type[i_exec] == REDIR_L)
		do_redir_l(mini_sh, i_exec);
	(void)i_exec;
	(void)mini_sh;
	return (SUCCESS);
}

int	is_there_a_redir(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type && is_sep_int(tmp->type) == SUCCESS && tmp->type != PIPE)
			return (SUCCESS);
		tmp = tmp->next;
	}
	return (FAIL);
	// int i = 0;
	// while(mini_sh->prepare_exec[i_exec][i])
	// {
	// 	if (mini_sh->sep_type[i])
	// }
	// if (mini_sh->sep_type && mini_sh->sep_type[i_exec] != FAIL && mini_sh->sep_type[i_exec] != PIPE)
	// 	return (SUCCESS);
	// else
	// 	return (FAIL);
}

void	travel_through_the_read(t_mini_sh *mini_sh, int i_exec)
{
	int i;
	int j;
	int p;
	
	i = i_exec;
	j = 0;
	p = 0;
	while (mini_sh->sep_type && mini_sh->sep_type[i] != FAIL && mini_sh->sep_type[i] != PIPE)
	{
		if (mini_sh->sep_type[i] == REDIR_L)
		{
			mini_sh->exec->fd_in = mini_sh->exec->fd_l[j];
			j++;
		}
		else if (mini_sh->sep_type[i] == HR_DOC)
		{
			mini_sh->exec->fd_in = mini_sh->exec->fd_hr[p];
			p++;
		}
		i++;
	}
}

int	init_fd_exec(t_mini_sh *mini_sh, int i_exec)
{
	if (i_exec == 0)
		mini_sh->exec->fd_in = 0;
	else if (i_exec > 0 && mini_sh->len_prepare_exec - 1 != i_exec)
		mini_sh->exec->fd_in = mini_sh->exec->tab_fd[i_exec - 1][0];
	else
	{
		if (mini_sh->sep_type[i_exec - 1] != REDIR_L && mini_sh->sep_type[i_exec - 1] != HR_DOC)
			mini_sh->exec->fd_in = mini_sh->exec->tab_fd[i_exec - 1][0];
		else
		{
			if (mini_sh->sep_type[i_exec - 1] == REDIR_L)
				mini_sh->exec->fd_in = mini_sh->exec->fd_l[mini_sh->exec->check_l];
			else if (mini_sh->sep_type[i_exec - 1] == HR_DOC)
				mini_sh->exec->fd_in = mini_sh->exec->fd_hr[mini_sh->exec->check_hr];
		}
	}
	if (i_exec + 1 == mini_sh->len_prepare_exec)
		mini_sh->exec->fd_out = 1;
	else
		mini_sh->exec->fd_out = mini_sh->exec->tab_fd[i_exec][1];
	// printf("\n.....................................\n\n");
	// printf(BACK_RED"mini_sh->exec->fd_out: %i"RST"\n", mini_sh->exec->fd_out);
	// printf(BACK_RED"(i_exec + 1): %i"RST"\n", (i_exec + 1));
	// printf(BACK_RED"mini_sh->len_prepare_exec: %i"RST"\n", mini_sh->len_prepare_exec);
	// printf("\n.....................................\n\n");
	if (is_there_a_redir(mini_sh) == SUCCESS)
		exec_redir(mini_sh, i_exec);
	return (SUCCESS);
}

void	close_rdr(int *tab_rdr, int nbr_rdr)
{
	int	i_cls_rdr;

	i_cls_rdr = -1;
	while (++i_cls_rdr < nbr_rdr)
	{
		if (tab_rdr[i_cls_rdr] > 2 && tab_rdr[i_cls_rdr] < 1024)
			close(tab_rdr[i_cls_rdr]);
	}
}

int	first_is_a_redir(t_mini_sh *mini_sh)
{
	t_parse *tmp;
	
	tmp = mini_sh->rl_out_head;
	if (is_all(tmp->type) == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

void	close_all(t_mini_sh *mini_sh)
{
	int	i;

	i = 0;
	if (mini_sh->redir_alone == SUCCESS)
	{
		// printf(BACK_RED"alone"RST"\n");
		if (mini_sh->exec->tab_fd && mini_sh->exec->tab_fd[i] && mini_sh->exec->tab_fd[i][0] > 2)
		{
			// printf(BACK_PURPLE"close[0] : %i"RST"\n", mini_sh->exec->tab_fd[i][0]);
			close(mini_sh->exec->tab_fd[i][0]);
		}
		if (mini_sh->exec->tab_fd && mini_sh->exec->tab_fd[i] && mini_sh->exec->tab_fd[i][1] > 2)
		{
			// printf(BACK_PURPLE"close[1] : %i"RST"\n", mini_sh->exec->tab_fd[i][1]);
			close(mini_sh->exec->tab_fd[i][1]);
		}
	}
	else {
		// printf(BACK_RED"multi"RST"\n");
		if (first_is_a_redir(mini_sh) == SUCCESS)
		{
			// printf(RED"first"RST"\n");
			if (mini_sh->exec->tab_fd && mini_sh->exec->tab_fd[i] && mini_sh->exec->tab_fd[i][0] > 2)
			{
				// printf(BACK_PURPLE"close[0] : %i"RST"\n", mini_sh->exec->tab_fd[i][0]);
				close(mini_sh->exec->tab_fd[i][0]);
			}
			if (mini_sh->exec->tab_fd && mini_sh->exec->tab_fd[i] && mini_sh->exec->tab_fd[i][1] > 2)
			{
				// printf(BACK_PURPLE"close[1] : %i"RST"\n", mini_sh->exec->tab_fd[i][1]);
				close(mini_sh->exec->tab_fd[i][1]);
			}
			// i++;
		}
		while (i < mini_sh->sep_2 + 1)
		{
			// printf(RED"all"RST"\n");
			if (mini_sh->exec->tab_fd && mini_sh->exec->tab_fd[i] && mini_sh->exec->tab_fd[i][0] > 2)
			{
				// printf(BACK_PURPLE"close[0] : %i"RST"\n", mini_sh->exec->tab_fd[i][0]);
				close(mini_sh->exec->tab_fd[i][0]);
			}
			if (mini_sh->exec->tab_fd && mini_sh->exec->tab_fd[i] && mini_sh->exec->tab_fd[i][1] > 2)
			{
				// printf(BACK_PURPLE"close[1] : %i"RST"\n", mini_sh->exec->tab_fd[i][1]);
				close(mini_sh->exec->tab_fd[i][1]);
			}
			i++;
		}
	}
	if (mini_sh->exec->nbr_fd_r > 0)
		close_rdr(mini_sh->exec->fd_r, mini_sh->exec->nbr_fd_r);
	if (mini_sh->exec->nbr_fd_l > 0)
		close_rdr(mini_sh->exec->fd_l, mini_sh->exec->nbr_fd_l);
	if (mini_sh->exec->nbr_fd_hr > 0)
		close_rdr(mini_sh->exec->fd_hr, mini_sh->exec->nbr_fd_hr);
	if (mini_sh->exec->nbr_fd_app > 0)
		close_rdr(mini_sh->exec->fd_app, mini_sh->exec->nbr_fd_app);
}

void	child_process(t_mini_sh *mini_sh, int i_exec)
{
	if (init_fd_exec(mini_sh, i_exec) == FAIL)
		exit (1);
//	travel_through_the_read(mini_sh, i_exec);
	fprintf(stderr, BACK_PURPLE" %s "PURPLE"\nin : %i\nout : %i\n\n"RST, mini_sh->prepare_exec[i_exec][0], mini_sh->exec->fd_in, mini_sh->exec->fd_out);
	exec_signal(4);
	dup2(mini_sh->exec->fd_in, 0);
	dup2(mini_sh->exec->fd_out, 1);
	close_all(mini_sh);
	if (do_built_in(mini_sh, i_exec) == FAIL)
		exec_cmd(mini_sh, i_exec);
	free_all(mini_sh);
	exit (1);
}

int	count_redir_in_line(t_mini_sh *mini_sh, int type)
{
	t_parse *temp;

	while (mini_sh->rl_check_redir)
	{
		if (mini_sh->rl_check_redir->type == type)
		{
			temp = mini_sh->rl_check_redir->next;
			while (temp)
			{
				if (is_sep(temp->word) == SUCCESS)
				{
					if (temp->type == type)
						return(SUCCESS);
					else
						return (FAIL);
				}
				temp = temp->next;
			}
		}
		mini_sh->rl_check_redir = mini_sh->rl_check_redir->next;
	}
	return (SUCCESS);
}

void	increase_check(t_mini_sh *mini_sh, int i_exec, int type)
{
	if (i_exec < mini_sh->sep_2 && i_exec < mini_sh->len_prepare_exec - 2)
	{
		if (type == REDIR_R)
		{
			if (mini_sh->exec->check_r < mini_sh->exec->nbr_fd_r)
			{
				// printf(BOLD_RED"check_r = %d"RST"\n", mini_sh->exec->check_r);
				if (count_redir_in_line(mini_sh, type) == FAIL)
					mini_sh->exec->check_r++;
				// printf(BOLD_RED"after check_r = %d"RST"\n", mini_sh->exec->check_r);
				// else
				// 	mini_sh->exec->check_r = mini_sh->exec->check_r;
			}
		}
		else if (type == APPEND)
		{
			if (mini_sh->exec->check_app < mini_sh->exec->nbr_fd_app)
			{
				if (count_redir_in_line(mini_sh, type) == FAIL)
					mini_sh->exec->check_app++;
				// else
				// 	mini_sh->exec->check_app = mini_sh->exec->check_app;
			}
		}
		else if (type == HR_DOC)
		{
			if (mini_sh->exec->check_hr < mini_sh->exec->nbr_fd_hr)
			{
				if (count_redir_in_line(mini_sh, type) == FAIL)
					mini_sh->exec->check_hr++;
			}
		}
		else if (type == REDIR_L)
		{
			if (mini_sh->exec->check_l < mini_sh->exec->nbr_fd_l)
			{
				if (count_redir_in_line(mini_sh, type) == FAIL)
					mini_sh->exec->check_l++;
			//mini_sh->exec->clk_l++;
			}
		}
	}
}

int	start_exec(t_mini_sh *mini_sh)
{
	int	i_exec;

	i_exec = 0;
	//g_exit_stt = 0;
	g_exit_stt = 0;
	mini_sh->pids = (pid_t *)malloc((sizeof (pid_t)) * (mini_sh->sep_2 + 1));
	if (!mini_sh->pids)
		return (FAIL_MALLOC);
	mini_sh->rl_check_redir = mini_sh->rl_out_head;
	if (mini_sh->exec->nbr_fd_hr > 0)
		exec_all_hr_doc(mini_sh);
	while (mini_sh->prepare_exec[i_exec])
	{
		if (g_exit_stt == 130)
			return (FAIL);
		if (exec_builtin(mini_sh, i_exec) == FAIL)
		{
			mini_sh->pids[i_exec] = fork();
			if (mini_sh->pids[i_exec] == -1)
				return (FAIL);
			if (mini_sh->pids[i_exec] == 0)
				child_process(mini_sh, i_exec);
		}
		else
			mini_sh->pids[i_exec] = FAIL;
		if (mini_sh->sep_type && i_exec < mini_sh->sep_2)
		{
			// printf(BACK_PURPLE"i_exec: %i"RST"\n", i_exec);
			// printf(BACK_PURPLE"mini_sh->sep_type[i_exec]: %i"RST"\n", mini_sh->sep_type[i_exec]);
			// printf("\n.....................................\n\n");
			increase_check(mini_sh, i_exec, mini_sh->sep_type[i_exec]);
		}
		i_exec++;
	}
	close_all(mini_sh);
	i_exec = 0;
	//exit_status(mini_sh, i_exec);
	int	err;
	while (mini_sh->prepare_exec[i_exec] && mini_sh->pids && mini_sh->pids[i_exec] && mini_sh->pids[i_exec] != FAIL)
	{
		// printf("g_exit_stt : %d\n", g_exit_stt);
		if (mini_sh->pids[i_exec] != FAIL)
			waitpid(mini_sh->pids[i_exec], &g_exit_stt, 0);
		// printf("start  err : %d\n", g_exit_stt);
		if (WIFEXITED(g_exit_stt))
		{
			//err = WIFEXITED(g_exit_stt);
			// printf("bef err : %d\n", g_exit_stt);
			err = WEXITSTATUS(g_exit_stt);
			// printf("aft err : %d\n", err);
			g_exit_stt = err;
			// fprintf(stderr, "mini_sh->prepare_exec[%i][0] = %s\n", i_exec, mini_sh->prepare_exec[i_exec][0]);
			// printf("exit_stt : %d\n", g_exit_stt);
		}
		else if (WIFSIGNALED(g_exit_stt))
			g_exit_stt = 128 + WTERMSIG(g_exit_stt);
		if (g_exit_stt == 131)
			write(1, "Quit (core dumped)\n", 19);
		i_exec++;
	}
	// close_all(mini_sh);
	if (mini_sh->exec->nbr_fd_hr > 0)
		unlink_hr_dc(mini_sh);
	exec_signal(1);
	return (SUCCESS);
}

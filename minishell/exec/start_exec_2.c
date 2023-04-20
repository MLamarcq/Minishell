/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:33:14 by mael              #+#    #+#             */
/*   Updated: 2023/04/20 18:43:12 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int g_exit_stt;

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
		mini_sh->sep_type = (int *)malloc(sizeof(int) * (mini_sh->sep_2 + 1));
	if (!mini_sh->sep_type)
		return (FAIL_MALLOC);
	i = 0;
	while (tmp)
	{
		if (is_sep(tmp->word) == SUCCESS && tmp->type)
		{
			printf("tmptype %i\n", tmp->type);
			printf(BACK_PURPLE"i: %i"RST"\n", i + 1);
			printf(BACK_PURPLE"mini_sh->sep_2: %i"RST"\n", mini_sh->sep_2);
			mini_sh->sep_type[i] = tmp->type;
			printf("sep typ %i\n", mini_sh->sep_type[i]);
			i++;
		}
		tmp = tmp->next;
	}
	mini_sh->sep_type[i] = 0;
	mini_sh->sep_id = 0;
	return (SUCCESS);
}

void	print_cmd_not_found(t_mini_sh *mini_sh, int i_exec)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(mini_sh->prepare_exec[i_exec][0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_all(mini_sh);
	exit (127);
}

void	exec_cmd(t_mini_sh *mini_sh, int i_exec)
{
	char	*cmd_abs_path;

	//printf("fbfdbd\n");
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
	//printf(BACK_CYAN"mini_sh->sep_type: %p"RST"\n", mini_sh->sep_type);
	if (mini_sh->sep_type && mini_sh->sep_type[i_exec] == REDIR_R)
		do_redir_r(mini_sh, i_exec);
	else if (mini_sh->sep_type && mini_sh->sep_type[i_exec] == APPEND)
	{
		printf(BLUE"ici"RST"\n");
		do_append(mini_sh, i_exec);
	}
	else if (mini_sh->sep_type && mini_sh->sep_type[i_exec] == HR_DOC)
	{
		printf(YELLOW"on est bien dans le hr"RST"\n");
		do_heredoc_redir(mini_sh, i_exec);
	}
	else if (mini_sh->sep_type && mini_sh->sep_type[i_exec] == REDIR_L)
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
	if (is_there_a_redir(mini_sh) == SUCCESS)
		exec_redir(mini_sh, i_exec);
	return (SUCCESS);
}

void	close_all(t_mini_sh *mini_sh)
{
	int i;

	i = 0;
	while (i < mini_sh->sep_2)
	{
		if (mini_sh->exec->tab_fd[i][0] > 2)
			close(mini_sh->exec->tab_fd[i][0]);
		if (mini_sh->exec->tab_fd[i][1] > 2)
			close(mini_sh->exec->tab_fd[i][1]);
		i++;
	}
}

void	child_process(t_mini_sh *mini_sh, int i_exec)
{
	if (init_fd_exec(mini_sh, i_exec) == FAIL)
		exit (1);
	printf("in = %d\n", mini_sh->exec->fd_in);
	printf("out = %d\n", mini_sh->exec->fd_out);
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
					printf("->%s\n", mini_sh->rl_check_redir->word);
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
	// if (mini_sh->sep_type[i_exec] == REDIR_R)
	// 	mini_sh->exec->check_r++;
	// else if (mini_sh->sep_type[i_exec] == APPEND)
	// 	mini_sh->exec->check_app++;
	// else if (mini_sh->sep_type[i_exec] == HR_DOC)
	// 	mini_sh->exec->check_hr+f (mini_sh->sep_type)
	if (i_exec < mini_sh->sep_2 && i_exec < mini_sh->len_prepare_exec - 2)
	{
		if (type == REDIR_R)
		{
			//printf(PURPLE"i_exec = %d"RST"\n", i_exec);
			if (mini_sh->exec->check_r < mini_sh->exec->nbr_fd_r)
			{
				//printf(BACK_BLUE"-> ici, check"RST"\n");
				printf(BOLD_RED"check_r = %d"RST"\n", mini_sh->exec->check_r);
				if (count_redir_in_line(mini_sh, type) == FAIL)
					mini_sh->exec->check_r++;
				printf(BOLD_RED"after check_r = %d"RST"\n", mini_sh->exec->check_r);
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
		// cat<main.c>t1|cat<Makefile>t2|cat<<eof>t3>t4
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



// void	increase_check(t_mini_sh *mini_sh, int i_exec)
// {
// 	// if (mini_sh->sep_type[i_exec] == REDIR_R)
// 	// 	mini_sh->exec->check_r++;
// 	// else if (mini_sh->sep_type[i_exec] == APPEND)
// 	// 	mini_sh->exec->check_app++;
// 	// else if (mini_sh->sep_type[i_exec] == HR_DOC)
// 	// 	mini_sh->exec->check_hr++;
// 	if (i_exec < mini_sh->sep_2 && i_exec < mini_sh->len_prepare_exec - 2)
// 	{
// 		if (mini_sh->sep_type[i_exec] == REDIR_R)
// 		{
// 			printf(PURPLE"i_exec = %d"RST"\n", i_exec);
// 			if (mini_sh->exec->check_r < mini_sh->exec->nbr_fd_r)
// 			{
// 				printf(BACK_BLUE"-> ici, check"RST"\n");
// 				if (count_redir_in_line(mini_sh) == FAIL)
// 					mini_sh->exec->check_r++;
// 				else
// 					mini_sh->exec->check_r = mini_sh->exec->check_r;
// 			}
// 		}
// 		else if (mini_sh->sep_type[i_exec] == APPEND)
// 		{
// 			if (mini_sh->exec->check_app < mini_sh->exec->nbr_fd_app)
// 			{
// 				if (count_redir_in_line(mini_sh) == FAIL)
// 					mini_sh->exec->check_app++;
// 				else
// 					mini_sh->exec->check_app = mini_sh->exec->check_app;
// 			}
// 		}
// 		else if (mini_sh->sep_type[i_exec] == HR_DOC)
// 			mini_sh->exec->check_hr++;
// 	}
// }

int	start_exec(t_mini_sh *mini_sh)
{
	int i_exec;
	int err;
	
	i_exec = 0;
	mini_sh->pids = (pid_t *)malloc((sizeof (pid_t)) * (mini_sh->sep_2 + 1));
	if (!mini_sh->pids)
		return (FAIL_MALLOC);
	mini_sh->rl_check_redir = mini_sh->rl_out_head;
	if (mini_sh->exec->nbr_fd_hr > 0)
		exec_all_hr_doc(mini_sh);
	printf(RED"g = %d"RST"\n", g_exit_stt);
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
		if (mini_sh->sep_type)
			increase_check(mini_sh, i_exec, mini_sh->sep_type[i_exec]);
		i_exec++;
	}
	close_all(mini_sh);
	i_exec = 0;
	while (mini_sh->prepare_exec[i_exec])
	{
		printf("g_exit_status : %d\n", g_exit_stt);
		if (mini_sh->pids[i_exec] != FAIL)
			waitpid(mini_sh->pids[i_exec], &g_exit_stt, 0);
		printf("start  err : %d\n", g_exit_stt);
		if (WIFEXITED(g_exit_stt))
		{
			//err = WIFEXITED(g_exit_stt);
			printf("bef err : %d\n", g_exit_stt);
			err = WEXITSTATUS(g_exit_stt);
			printf("aft err : %d\n", err);
			g_exit_stt = err;
			fprintf(stderr, "mini_sh->prepare_exec[%i][0] = %s\n", i_exec, mini_sh->prepare_exec[i_exec][0]);
			printf("exit_status : %d\n", g_exit_stt);
		}
		i_exec++;
	}
	if (mini_sh->exec->nbr_fd_hr > 0)
		unlink_hr_dc(mini_sh);
	return (SUCCESS);
}

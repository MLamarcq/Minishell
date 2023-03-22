/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:33:14 by mael              #+#    #+#             */
/*   Updated: 2023/03/22 16:50:26 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	init_sep_type(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	int		i;

	tmp = mini_sh->rl_out_head;
	mini_sh->sep_type = (int*)malloc(sizeof(int) * (mini_sh->sep_2 + 1));
	if (!mini_sh->sep_type)
		return (FAIL_MALLOC);
	i = 0;
	while (tmp)
	{
		if (is_sep(tmp->word) == SUCCESS)
		{
			mini_sh->sep_type[i] = tmp->type;
			i++;
		}
		tmp = tmp->next;
	}
	mini_sh->sep_type[i] = 0;
	// i = 0;
	// while (mini_sh->sep_type[i])
	// {
	// 	if (mini_sh->sep_type[i] == PIPE)
	// 		printf(BLUE"PIPE\n"RST);
	// 	else if (mini_sh->sep_type[i] == REDIR_L)
	// 		printf(BLUE"REDIR_L\n"RST);
	// 	else if (mini_sh->sep_type[i] == REDIR_R)
	// 		printf(BLUE"REDIR_R\n"RST);
	// 	else if (mini_sh->sep_type[i] == APPEND)
	// 		printf(BLUE"APPEND\n"RST);
	// 	else if (mini_sh->sep_type[i] == HR_DOC)
	// 		printf(BLUE"HR_DOC\n"RST);
	// 	else
	// 		printf("other type = %d\n", mini_sh->sep_type[i]);
	// 	i++;
	// }
	// printf("\ni = %d\n", i);
	return (SUCCESS);
}

/*
int	if_pipe(t_mini_sh *mini_sh, int i)
{
	printf("mini_sh->exec->pipe_id: %i\n", mini_sh->exec->pipe_id);
	if (mini_sh->exec->pipe_id == 0)
	{
		dup2(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][0], STDIN_FILENO);
		dup2(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][1], STDOUT_FILENO);
	}
	else if (mini_sh->exec->tab_fd[mini_sh->exec->pipe_id + 1])
	{
		dup2(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][0], mini_sh->exec->tab_fd[mini_sh->exec->pipe_id - 1][1]);
		dup2(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][1], mini_sh->exec->tab_fd[mini_sh->exec->pipe_id + 1][0]);
	}
	else
	{
		dup2(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][0], mini_sh->exec->tab_fd[mini_sh->exec->pipe_id - 1][1]);
		dup2(STDOUT_FILENO, mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][1]);
	}
	close(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][0]);
	close(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][1]);
	mini_sh->exec->pipe_id++;
	if (<do_built_in(>mini_sh) == FAIL)
		exec_cmd(mini_sh, i);
	return (SUCCESS);
}
*/

void	exec_cmd(t_mini_sh *mini_sh, int i_exec)
{
	char *cmd_abs_path;

	cmd_abs_path = NULL;
	if (access(mini_sh->prepare_exec[i_exec][0], X_OK) == 0)
	{
		execve(mini_sh->prepare_exec[i_exec][0], mini_sh->prepare_exec[i_exec], mini_sh->env);
		// if execve then free; exit status
	}
	cmd_abs_path = ft_find_path_2(mini_sh, mini_sh->prepare_exec[i_exec][0]);
	if (cmd_abs_path != NULL)
	{
		free(mini_sh->prepare_exec[i_exec][0]);
		mini_sh->prepare_exec[i_exec][0] = cmd_abs_path;
		execve(cmd_abs_path, mini_sh->prepare_exec[i_exec], mini_sh->env);
	}
	else
	{
		printf("minishell:%s: command not found\n", mini_sh->prepare_exec[i_exec][0]);
		exit (127);
	}
}

int	init_tab_fd(t_mini_sh *mini_sh)
{
	int	i_init_fd;

	i_init_fd = 0;
	mini_sh->exec->tab_fd = malloc(sizeof(int *) * (mini_sh->len_prepare_exec + 1));
	if (!mini_sh->exec->tab_fd)
		return (FAIL_MALLOC);
	mini_sh->exec->tab_fd[mini_sh->len_prepare_exec] = 0;
	while (mini_sh->prepare_exec[i_init_fd + 1])
	{
		mini_sh->exec->tab_fd[i_init_fd] = malloc(sizeof(int) * 3);
		mini_sh->exec->tab_fd[i_init_fd][2] = 0;
		if (pipe(mini_sh->exec->tab_fd[i_init_fd]) == -1)
			printf(BACK_RED"pipe not working"RST"\n");
		// printf(BACK_BLUE"mini_sh->exec->tab_fd[%i][0]: %i"RST"\n", i_init_fd, mini_sh->exec->tab_fd[i_init_fd][0]);
		// printf(BACK_BLUE"mini_sh->exec->tab_fd[%i][1]: %i"RST"\n", i_init_fd, mini_sh->exec->tab_fd[i_init_fd][1]);
		i_init_fd++;
	}
	return (SUCCESS);
	(void)i_init_fd;
}

void	print_sep(t_mini_sh *mini_sh)
{
	int	i_print_sep;

	i_print_sep = -1;
	while (mini_sh->sep_type[++i_print_sep])
		print_type(mini_sh->sep_type[i_print_sep]);
}

int	child_process(t_mini_sh *mini_sh, int i_exec)
{
	int	i_close;

	i_close = 0;
	
	// print_sep(mini_sh);
	// printf(BACK_PURPLE"sep > 0     : %i"RST"\n", mini_sh->sep_type[i_exec] > 0);
	// printf(BACK_PURPLE"!sep_type   : %i"RST"\n", !mini_sh->sep_type[i_exec]);
	// printf(BOLD_PURPLE"i_exec      : %i"RST"\n", mini_sh->sep_type[i_exec]);
	if (mini_sh->sep_type[i_exec] && i_exec == 0)
	{
		if (mini_sh->sep_type[i_exec] == PIPE)
		{
			
			fprintf(stderr, BOLD_YELLOW"start	"YELLOW"dup(%i, %i)\n"RST, mini_sh->exec->tab_fd[i_exec][1], STDOUT_FILENO);
			dup2(mini_sh->exec->tab_fd[i_exec][1], STDOUT_FILENO);
			dup2(0, 0);
			i_close = 0;
			while (mini_sh->exec->tab_fd[i_close])
			{
				close(mini_sh->exec->tab_fd[i_close][0]);
				close(mini_sh->exec->tab_fd[i_close][1]);
				i_close++;
			}
			exec_cmd(mini_sh, i_exec);
		}
	}
	else if (mini_sh->sep_type[i_exec] && mini_sh->sep_type[i_exec] > 0)
	{
		if (mini_sh->sep_type[i_exec] == PIPE)
		{
			dup2(mini_sh->exec->tab_fd[i_exec - 1][0], 0);
			dup2(mini_sh->exec->tab_fd[i_exec][1], 1);
			fprintf(stderr, BOLD_YELLOW"middle	"YELLOW"dup(%i, %i) %s"RST"\n", mini_sh->exec->tab_fd[i_exec - 1][0], 0, mini_sh->prepare_exec[i_exec][0]);
			fprintf(stderr, BOLD_YELLOW"middle	"YELLOW"dup(%i, %i) %s"RST"\n", mini_sh->exec->tab_fd[i_exec][1], 1, mini_sh->prepare_exec[i_exec][0]);
			i_close = 0;
			while (mini_sh->exec->tab_fd[i_close])
			{
				close(mini_sh->exec->tab_fd[i_close][0]);
				close(mini_sh->exec->tab_fd[i_close][1]);
				i_close++;
			}
			exec_cmd(mini_sh, i_exec);
		}
	}
	else if ((mini_sh->sep_type[i_exec + 1] > 1024 || !mini_sh->sep_type[i_exec + 1]) && mini_sh->sep_type[i_exec - 1])
	{
		if (mini_sh->sep_type[i_exec - 1] == PIPE)
		{
			
			fprintf(stderr, BOLD_YELLOW"end	"YELLOW"dup(%i, %i)"RST"\n", mini_sh->exec->tab_fd[i_exec - 1][0], STDIN_FILENO);
			dup2(mini_sh->exec->tab_fd[i_exec - 1][0], STDIN_FILENO);
			dup2(1, 1);
			i_close = 0;
			while (mini_sh->exec->tab_fd[i_close])
			{
				close(mini_sh->exec->tab_fd[i_close][0]);
				close(mini_sh->exec->tab_fd[i_close][1]);
				i_close++;
			}
			exec_cmd(mini_sh, i_exec);
		}
	}
	else
	{
		printf(BACK_RED"alone"RST"\n");
		fprintf(stderr, BLUE"Previous(%i, %i)"RST"\n", mini_sh->sep_type[i_exec + 1], mini_sh->sep_type[i_exec - 1]);
		dup2(0, 0);
		dup2(1, 1);
		exec_cmd(mini_sh, i_exec);
	}
	// if (do_built_in(mini_sh) == FAIL)
	return (SUCCESS);
	(void)i_close;
}

int	start_exec(t_mini_sh *mini_sh)
{
	int i_exec;

	i_exec = 0;
	mini_sh->pids = (pid_t *)malloc((sizeof (pid_t)) * (mini_sh->sep_2 + 1));
	if (!mini_sh->pids)
		return (FAIL_MALLOC);
	while (mini_sh->prepare_exec[i_exec])
	{
		// if (is_built_in_2(mini_sh->prepare_exec[i_exec], mini_sh) == SUCCESS && (!mini_sh->prepare_exec[i_exec + 1]))
		// {
		// 	do_built_in(mini_sh);
		// 	break ;
		// }
		mini_sh->pids[i_exec] = fork();
		fprintf(stderr, CYAN"mini_sh->pids[%i]: %i"RST"\n", i_exec, mini_sh->pids[i_exec]);
		if (mini_sh->pids[i_exec] == -1)
			return (FAIL);
		if (mini_sh->pids[i_exec] == 0)
			child_process(mini_sh, i_exec);
		// else
		// 	waitpid(mini_sh->pids[i_exec], NULL, 0);

		if (mini_sh->prepare_exec[i_exec + 1])
			printf("\n.....................................\n\n");
		i_exec++;
	}
	i_exec = 0;
	while (i_exec < mini_sh->sep_2)
	{
		if (mini_sh->exec->tab_fd[i_exec][0] > 2)
			close(mini_sh->exec->tab_fd[i_exec][0]);
		if (mini_sh->exec->tab_fd[i_exec][1] > 2)
			close(mini_sh->exec->tab_fd[i_exec][1]);
		i_exec++;
	}
	// if (mini_sh->sep_2 >= 0)
	// {
		i_exec = 0;
		while (mini_sh->prepare_exec[i_exec])
		{
			waitpid(mini_sh->pids[i_exec], NULL, 0);
			i_exec++;
		}
	// }
	return (SUCCESS);
	// function while tous est 0
	// 
}

// char ** -> {PIPE, PIPE, REDIR_R, PIPE}
// STDOUT_FILENO	1	affichage	
// STDIN_FILENO		0	prompt		

// fd[0] lecture	dans le pipe
// fd[1] écriture	dans le pipe
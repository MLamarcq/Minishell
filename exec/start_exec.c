/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:33:14 by mael              #+#    #+#             */
/*   Updated: 2023/03/17 16:08:23 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	init_sep_type(t_mini_sh *mini_sh)
{
	t_parse *tmp;
	int i;

	tmp = mini_sh->rl_out_head;
	printf("nbr sep = %d\n", mini_sh->sep_2);
	mini_sh->sep_type = (int*)malloc(sizeof(int) * mini_sh->sep_2 + 1);
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
	i = 0;
	while (mini_sh->sep_type[i])
	{
		if (mini_sh->sep_type[i] == PIPE)
			printf(BLUE"PIPE\n"RST);
		else if (mini_sh->sep_type[i] == REDIR_L)
			printf(BLUE"REDIR_L\n"RST);
		else if (mini_sh->sep_type[i] == REDIR_R)
			printf(BLUE"REDIR_R\n"RST);
		else if (mini_sh->sep_type[i] == APPEND)
			printf(BLUE"APPEND\n"RST);
		else if (mini_sh->sep_type[i] == HR_DOC)
			printf(BLUE"HR_DOC\n"RST);
		else
			printf("other type = %d\n", mini_sh->sep_type[i]);
		i++;
	}
	printf("\ni = %d\n", i);
	return (SUCCESS);
}

// int	if_pipe(t_mini_sh *mini_sh, int i)
// {
// 	printf("mini_sh->exec->pipe_id: %i\n", mini_sh->exec->pipe_id);
// 	if (mini_sh->exec->pipe_id == 0)
// 	{
// 		dup2(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][0], STDIN_FILENO);
// 		dup2(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][1], STDOUT_FILENO);
// 	}
// 	else if (mini_sh->exec->tab_fd[mini_sh->exec->pipe_id + 1])
// 	{
// 		dup2(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][0], mini_sh->exec->tab_fd[mini_sh->exec->pipe_id - 1][1]);
// 		dup2(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][1], mini_sh->exec->tab_fd[mini_sh->exec->pipe_id + 1][0]);
// 	}
// 	else
// 	{
// 		dup2(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][0], mini_sh->exec->tab_fd[mini_sh->exec->pipe_id - 1][1]);
// 		dup2(STDOUT_FILENO, mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][1]);
// 	}
// 	close(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][0]);
// 	close(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][1]);
// 	mini_sh->exec->pipe_id++;
// 	if (do_built_in(mini_sh) == FAIL)
// 		test_exec(mini_sh, i);
// 	return (SUCCESS);
// }


int	child_process(t_mini_sh *mini_sh, int i)
{
	int j = 0;
	
	if (i >= 1)
	{
		if (mini_sh->sep_type[j] == PIPE)
				if_pipe(mini_sh, i);
	}
	if (do_built_in(mini_sh) == FAIL)
	 	test_exec(mini_sh, i);
	return (SUCCESS);
}

// int	is_all_pids_full(t_mini_sh *mini_sh)
// {
// 	int	i;
// 
// 	i = 0;
// 	while (mini_sh->pids[i])
// 	{
// 		if (mini_sh->pids[i] == 0)
// 			return (FAIL);
// 	}
// 	return (SUCCESS);
// }

int	start_exec(t_mini_sh *mini_sh)
{
	int i;

	i = 0;
	mini_sh->pids = (pid_t *)malloc((sizeof (pid_t)) * (mini_sh->sep_2 + 1));
	if (!mini_sh->pids)
		return (FAIL_MALLOC);
	while (mini_sh->prepare_exec[i])
	{
		mini_sh->pids[i] = fork();
		if (mini_sh->pids[i] == -1)
			return (FAIL);
		if (mini_sh->pids[i] == 0)
			child_process(mini_sh, i);
		else
			waitpid(mini_sh->pids[i], NULL, 0);
		fprintf(stderr, BACK_PURPLE"mini_sh->pids[%i]: %i"RST"\n", i, mini_sh->pids[i]);
		i++;
	}
	// i = 0;
	// while (mini_sh->pids[i])
	// {
	// 	waitpid(mini_sh->pids[i], NULL, 0);
	// 	i++;
	// }
	return (SUCCESS);
	// function while tous est 0
	// 
}

// char ** -> {PIPE, PIPE, REDIR_R, PIPE}

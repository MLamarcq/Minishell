/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:33:14 by mael              #+#    #+#             */
/*   Updated: 2023/03/25 14:53:34 by mael             ###   ########.fr       */
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
	mini_sh->sep_id = 0;
	return (SUCCESS);
}

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
		if (mini_sh->sep_type[i_exec] != PIPE)
			return ;
		printf("minishell:%s: command not found\n", mini_sh->prepare_exec[i_exec][0]);
		exit (127);
	}
}

int	init_tab_fd(t_mini_sh *mini_sh)
{
	int	i_init_fd;

	i_init_fd = 0;
	mini_sh->exec->tab_fd = malloc(sizeof(int *) * (mini_sh->sep_2 + 1));
	if (!mini_sh->exec->tab_fd)
		return (FAIL_MALLOC);
	mini_sh->exec->tab_fd[mini_sh->sep_2] = 0;
	while (i_init_fd < mini_sh->sep_2)
	{
		mini_sh->exec->tab_fd[i_init_fd] = malloc(sizeof(int) * 3);
		mini_sh->exec->tab_fd[i_init_fd][2] = 0;
		if (pipe(mini_sh->exec->tab_fd[i_init_fd]) == -1)
			return (printf(BACK_RED"pipe not working"RST"\n"), FAIL);
		i_init_fd++;
	}
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
			return (SUCCESS);
	}
	return (FAIL);
}

int	if_redir(t_mini_sh *mini_sh, int i_exec)
{
	printf("i_exec before if = %i\n", i_exec);
	if (mini_sh->sep_type[i_exec] && mini_sh->sep_type[i_exec] == REDIR_R)
	{
		printf("i_exec after if = %d\n", i_exec);
		mini_sh->exec->fd_r = open(mini_sh->prepare_exec[i_exec + 1][0], O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (!mini_sh->exec->fd_r)
			return (printf("Failure during opening redir_r file\n"), FAIL);
		close(mini_sh->exec->tab_fd[i_exec][1]);
		mini_sh->exec->fd_out = mini_sh->exec->fd_r;
	}
	return (SUCCESS);
}

int	init_fd_exec(t_mini_sh *mini_sh, int i_exec)
{
	if (i_exec == 0)
		mini_sh->exec->fd_in = 0;
	else
		mini_sh->exec->fd_in = mini_sh->exec->tab_fd[i_exec - 1][0];
	if (i_exec + 1 == mini_sh->len_prepare_exec)
		mini_sh->exec->fd_out = 1;
	else
		mini_sh->exec->fd_out = mini_sh->exec->tab_fd[i_exec][1];
	if_redir(mini_sh, i_exec);
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
	init_fd_exec(mini_sh, i_exec);
	dup2(mini_sh->exec->fd_in, 0);
	dup2(mini_sh->exec->fd_out, 1);
	close_all(mini_sh);
	if (exec_builtin(mini_sh, i_exec) == FAIL)
		exec_cmd(mini_sh, i_exec);
	exit (1);
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
		if (exec_builtin(mini_sh, i_exec) == FAIL)
		{
			mini_sh->pids[i_exec] = fork();
			if (mini_sh->pids[i_exec] == -1)
				return (FAIL);
			if (mini_sh->pids[i_exec] == 0)
				child_process(mini_sh, i_exec);
		}
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
	i_exec = 0;
	while (mini_sh->prepare_exec[i_exec])
	{
		waitpid(mini_sh->pids[i_exec], NULL, 0);
		i_exec++;
	}
	return (SUCCESS);
}
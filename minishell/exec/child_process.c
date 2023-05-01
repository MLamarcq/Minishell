/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:55:14 by ggosse            #+#    #+#             */
/*   Updated: 2023/05/01 22:16:51 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

char	*ft_find_cmd_2(t_mini_sh *mini_sh, int ite_env, char *cmd_to_find)
{
	char	**path_cmd;
	char	*cmd_path_absolue;
	char	*path_absolue;
	char	*cmd;
	int		ite_data;

	ite_data = -1;
	path_cmd = ft_split(mini_sh->env[ite_env] + 5, ':');
	cmd = ft_strdup(cmd_to_find);
	while (path_cmd[++ite_data])
	{
		path_absolue = ft_strjoin(path_cmd[ite_data], "/");
		cmd_path_absolue = ft_strjoin(path_absolue, cmd);
		free(path_absolue);
		if (access(cmd_path_absolue, X_OK) == 0)
		{
			ft_free_all(cmd, path_cmd);
			return (cmd_path_absolue);
		}
		else
			free(cmd_path_absolue);
	}
	ft_free_all(cmd, path_cmd);
	return (NULL);
}

char	*ft_find_path_2(t_mini_sh *mini_sh, char *cmd_to_find)
{
	int	ite_env;

	ite_env = -1;
	while (mini_sh->env[++ite_env])
	{
		if (ft_strncmp(mini_sh->env[ite_env], "PATH=", 4) == 0)
			return (ft_find_cmd_2(mini_sh, ite_env, cmd_to_find));
	}
	return (NULL);
}

int	init_fd_exec(t_mini_sh *mini, int i_exec)
{
	if (i_exec == 0)
		mini->exec->fd_in = 0;
	else if (i_exec > 0 && mini->len_prepare_exec - 1 != i_exec)
		mini->exec->fd_in = mini->exec->tab_fd[i_exec - 1][0];
	else
	{
		if (mini->sep_type[i_exec - 1] != REDIR_L \
		&& mini->sep_type[i_exec - 1] != HR_DOC)
			mini->exec->fd_in = mini->exec->tab_fd[i_exec - 1][0];
		else
		{
			if (mini->sep_type[i_exec - 1] == REDIR_L)
				mini->exec->fd_in = mini->exec->fd_l[mini->exec->check_l];
			else if (mini->sep_type[i_exec - 1] == HR_DOC)
				mini->exec->fd_in = mini->exec->fd_hr[mini->exec->check_hr];
		}
	}
	if (i_exec + 1 == mini->len_prepare_exec)
		mini->exec->fd_out = 1;
	else
		mini->exec->fd_out = mini->exec->tab_fd[i_exec][1];
	if (is_there_a_redir(mini) == SUCCESS)
		exec_redir(mini, i_exec);
	return (SUCCESS);
}

void	child_process(t_mini_sh *mini_sh, int i_exec)
{
	if (init_fd_exec(mini_sh, i_exec) == FAIL)
		exit (1);
	exec_signal(4);
	dup2(mini_sh->exec->fd_in, 0);
	dup2(mini_sh->exec->fd_out, 1);
	close_all(mini_sh);
	if (do_built_in(mini_sh, i_exec) == FAIL)
		exec_cmd(mini_sh, i_exec);
	free_all(mini_sh);
	exit (1);
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
		if (i_exec > 0 && mini_sh->sep_type && mini_sh->sep_type[i_exec - 1] \
		&& mini_sh->sep_type[i_exec - 1] != PIPE)
			end_exec_cmd(mini_sh);
		else if (i_exec == 0 && is_there_a_redir(mini_sh) == SUCCESS)
			end_exec_cmd(mini_sh);
		else
			print_cmd_not_found(mini_sh, i_exec);
	}
}

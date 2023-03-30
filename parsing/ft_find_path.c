/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:54:57 by ggosse            #+#    #+#             */
/*   Updated: 2023/03/30 12:33:05 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_find_cmd(t_mini_sh *mini_sh, int ite_env)
{
	char	**path_cmd;
	char	*cmd_path_absolue;
	char	*path_absolue;
	char	*cmd;
	int		ite_data;

	ite_data = -1;
	path_cmd = ft_split(mini_sh->env[ite_env] + 5, ':');
	cmd = ft_strdup(mini_sh->rl_out->word);
	while (path_cmd[++ite_data])
	{
		path_absolue = ft_strjoin(path_cmd[ite_data], "/");
		cmd_path_absolue = ft_strjoin(path_absolue, cmd);
		free(path_absolue);
		if (access(cmd_path_absolue, X_OK) == 0)
		{
			free(cmd_path_absolue);
			ft_free_all(cmd, path_cmd);
			return (SUCCESS);
		}
		// else
		// 	free(cmd_path_absolue);
	}
	ft_free_all(cmd, path_cmd);
	return (FAIL);
}

int	ft_find_path(t_mini_sh *mini_sh)
{
	int	ite_env;

	ite_env = -1;
	while (mini_sh->env[++ite_env])
	{
		if (ft_strncmp(mini_sh->env[ite_env], "PATH=", 4) == 0)
			return (ft_find_cmd(mini_sh, ite_env));
	}
	return (FAIL);
}

int	ft_find_env(t_mini_sh *mini_sh)
{
	if (!mini_sh->rl_out->word)
		return (FAIL);
	if (access(mini_sh->rl_out->word, X_OK) != 0)
	{
		if (mini_sh->env[0])
			return (ft_find_path(mini_sh));
	}
	return (FAIL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:54:57 by ggosse            #+#    #+#             */
/*   Updated: 2023/02/24 00:31:31 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_find_cmd(char **envp, char *cmd_to_test, int ite_env)
{
	char	**path_cmd;
	char	*cmd_path_absolue;
	char	*path_absolue;
	char	*cmd;
	int		ite_data;

	ite_data = -1;
	path_cmd = ft_split(envp[ite_env] + 5, ':');
	cmd = ft_strdup(cmd_to_test);
	while (path_cmd[++ite_data])
	{
		path_absolue = ft_strjoin(path_cmd[ite_data], "/");
		cmd_path_absolue = ft_strjoin(path_absolue, cmd);
		free(path_absolue);
		if(access(cmd_path_absolue, X_OK) == 0)
		{
			free(cmd_to_test);
			cmd_to_test = ft_strdup(cmd_path_absolue);
			cmd_to_test[ft_strlen(cmd_path_absolue)] = '\0';
			free(cmd_path_absolue);
			free(cmd);
			// ft_free_all(cmd, path_cmd);
			return (SUCCESS);
		}
		else
			free(cmd_path_absolue);
	}
	ft_free_all(cmd, path_cmd);
	return (FAIL);
}

int	ft_find_path(char **envp, char *cmd_to_test)
{
	int	ite_env;

	ite_env = -1;
	while (envp[++ite_env])
	{
		if (ft_strncmp(envp[ite_env], "PATH=", 5) == 0)
		{
			return (ft_find_cmd(envp, cmd_to_test, ite_env));
		}
	}
	return (FAIL);
}

int	ft_find_env(char **envp, char *cmd_to_test)
{
	if (!cmd_to_test)
		return (FAIL);
	if ((!access(cmd_to_test, X_OK)) == 0)
	{
		if (envp[0])
			return (ft_find_path(envp, cmd_to_test));
	}
	else
	{
		return (SUCCESS);
	}
	return (FAIL);
}

char	*ft_find_var_env(char **envp, char *var_search)
{
	char	*var_env;
	int		ite_env;
	int		ite_env_char;
	int		save;
	char	*res_var_env;

	res_var_env = NULL;
	save = 0;
	ite_env_char = 0;
	ite_env = -1;
	if (!var_search)
		return (NULL);
	if (envp[0])
	{
		var_env = ft_strdup(var_search);
		var_env = ft_strjoin(var_env, "=");
		while (envp[++ite_env])
		{
			ite_env_char = 0;
			while (envp[ite_env][ite_env_char] != '=')
				ite_env_char++;
			res_var_env = ft_strdup_len(envp[ite_env], 0, ite_env_char + 1);
			if (ft_strncmp(res_var_env, var_search, ft_strlen(var_search)) == 0)
			{
				ite_env_char++;
				save = ite_env_char;
				while (envp[ite_env][ite_env_char])
					ite_env_char++;
				free(res_var_env);
				return (ft_strdup_len(envp[ite_env], save, ite_env_char));
			}
			free(res_var_env);
		}
		free(var_env);
	}
	(void)ite_env_char;
	(void)ite_env;
	(void)var_env;
	return (NULL);
}

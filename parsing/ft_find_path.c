/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:54:57 by ggosse            #+#    #+#             */
/*   Updated: 2023/03/14 11:26:01 by mael             ###   ########.fr       */
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
		if(access(cmd_path_absolue, X_OK) == 0)
		{
			// free(mini_sh->rl_out->word);
			// mini_sh->rl_out->word = ft_strdup(cmd_path_absolue);
			// mini_sh->rl_out->word[ft_strlen(cmd_path_absolue)] = '\0';
			free(cmd_path_absolue);
			// free(cmd);
			ft_free_all(cmd, path_cmd);
			return (SUCCESS);
		}
		else
			free(cmd_path_absolue);
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
		if (ft_strncmp(mini_sh->env[ite_env], "PATH=", 5) == 0)
			return (ft_find_cmd(mini_sh, ite_env));
	}
	return (FAIL);
}

int	ft_find_env(t_mini_sh *mini_sh)
{
	if (!mini_sh->rl_out->word)
		return (FAIL);
	if ((!access(mini_sh->rl_out->word, X_OK)) == 0)
	{
		if (mini_sh->env[0])
			return (ft_find_path(mini_sh));
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
	char	*final;

	final = NULL;
	res_var_env = NULL;
	save = 0;
	ite_env_char = 0;
	ite_env = -1;
	if (!var_search)
		return (NULL);
	if (envp[0])
	{
		while (envp[++ite_env])
		{
			var_env = ft_strdup(var_search);
			var_env = ft_strjoin_lfree(var_env, "=");
			ite_env_char = 0;
			while (envp[ite_env][ite_env_char] != '=')
				ite_env_char++;
			res_var_env = ft_strdup_len(envp[ite_env], 0, ite_env_char + 1);
			if (ft_strncmp(res_var_env, var_env, ft_strlen(var_env)) == 0)
			{
				ite_env_char++;
				save = ite_env_char;
				while (envp[ite_env][ite_env_char])
					ite_env_char++;
				free(res_var_env);
				free(var_env);
				final = ft_strdup_len(envp[ite_env], save, ite_env_char);
				return (final);
			}
			free(res_var_env);
			free(var_env);
		}
	}
	(void)save;
	(void)ite_env_char;
	(void)ite_env;
	(void)var_env;
	return (NULL);
}

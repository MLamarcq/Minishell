/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:06:31 by gael              #+#    #+#             */
/*   Updated: 2023/04/20 16:02:42 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

char	*attr_var_found(char **envp, int ite_env, int ite_env_char, int save)
{
	char	*final;

	final = NULL;
	ite_env_char++;
	save = ite_env_char;
	while (envp[ite_env][ite_env_char])
		ite_env_char++;
	final = ft_strdup_len(envp[ite_env], save, ite_env_char);
	return (final);
}

char	*build_var_env(char *var_env, char *var_search, int *ite_env_char)
{
	var_env = ft_strdup(var_search);
	var_env = ft_strjoin_lfree(var_env, "=");
	(*ite_env_char) = 0;
	return (var_env);
}

void	init_res_var(char **res_varenv, int *save, int *i_char, int *i_env)
{
	(*res_varenv) = NULL;
	(*save) = 0;
	(*i_char) = 0;
	(*i_env) = -1;
}

char	*ft_find_var_env(char **envp, char *var_search)
{
	char	*res_var_env;
	char	*var_env;
	int		ite_env_char;
	int		ite_env;
	int		save;

	init_res_var(&res_var_env, &save, &ite_env_char, &ite_env);
	if (!var_search)
		return (NULL);
	if (envp[0])
	{
		while (envp[++ite_env])
		{
			var_env = build_var_env(var_env, var_search, &ite_env_char);
			while (envp[ite_env][ite_env_char] != '=')
				ite_env_char++;
			res_var_env = ft_strdup_len(envp[ite_env], 0, ite_env_char + 1);
			if (ft_strncmp(res_var_env, var_env, ft_strlen(var_env)) == 0)
				return (ft_free_var_env(var_env, res_var_env), \
				attr_var_found(envp, ite_env, ite_env_char, save));
			ft_free_var_env(var_env, res_var_env);
		}
	}
	return (NULL);
}

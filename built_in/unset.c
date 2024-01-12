/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:39:44 by mael              #+#    #+#             */
/*   Updated: 2023/04/28 14:55:47 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

int	to_empty_line(char **argv, t_mini_sh *mini_sh)
{
	mini_sh->data->env_ctt = ft_find_var_env(mini_sh->env, argv[1]);
	if (!argv || !argv[1])
		return (FAIL);
	while (mini_sh->env[mini_sh->data->i])
	{
		if (ft_strncmp(mini_sh->env[mini_sh->data->i], argv[1], \
		ft_strlen(argv[1]) - 1) == 0)
		{
			if (to_empty_line_utils(mini_sh, argv) != SUCCESS)
				return (FAIL);
			if (strcmp_empty_line(mini_sh) == SUCCESS)
				break ;
		}
		mini_sh->data->i++;
	}
	end_empty_line(mini_sh);
	return (SUCCESS);
}

int	check_unset_error(char **argv)
{
	int	i;

	if (ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) == 0)
	{
		i = 0;
		while (argv && argv[1] && argv[1][i])
		{
			if (argv[1][i] == '-')
			{
				if (i == 0)
					return (printf("minishell: unset: no option allowed\n"), \
					FAIL);
			}
			i++;
		}
	}
	return (SUCCESS);
}

int	unset(char **argv, t_mini_sh *mini_sh)
{
	if (check_unset_error(argv) == FAIL)
	{
		g_exit_stt = 1;
		return (FAIL);
	}
	if (ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) == 0)
	{
		if (to_empty_line(argv, mini_sh) < 0)
		{
			g_exit_stt = 1;
			return (FAIL);
		}
	}
	return (SUCCESS);
}

int	exec_unset(char **argv, t_mini_sh *mini_sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (unset(argv, mini_sh) == FAIL)
		return (FAIL);
	while (mini_sh->env[i])
	{
		if (mini_sh->env[i][j] == '\0')
		{
			free(mini_sh->env[i]);
			while (mini_sh->env[i + 1])
			{
				mini_sh->env[i] = ft_strdup(mini_sh->env[i + 1]);
				free(mini_sh->env[i + 1]);
				i++;
			}
			mini_sh->env[i] = '\0';
		}
		i++;
	}
	g_exit_stt = 0;
	return (SUCCESS);
}

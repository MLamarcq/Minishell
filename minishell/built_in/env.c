/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:43:53 by mael              #+#    #+#             */
/*   Updated: 2023/04/12 17:21:13 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	check_env(char **argv)
{
	if (ft_strncmp(argv[0], "env", ft_strlen(argv[0])) == 0)
	{
		if (argv[1] && argv[1][0] == '-')
		{
			printf("minishell: env: option are not allowed\n");
			return (FAIL);
		}
		else if (argv[1])
		{
			printf("minishell: env: argument are not allowed\n");
			return (FAIL);
		}
		return (SUCCESS);
	}
	else
		return (FAIL);
}

int	env(char **argv, t_mini_sh *mini_sh)
{
	int	j;

	if (check_env(argv) == FAIL)
		return (FAIL);
	if (ft_strncmp(argv[0], "env", ft_strlen(argv[0])) == 0)
	{
		j = 0;
		while (mini_sh->env[j])
		{
			printf("%s\n", mini_sh->env[j]);
			j++;
		}
		return (SUCCESS);
	}
	else
		printf("Command not found\n");
	return (FAIL);
}

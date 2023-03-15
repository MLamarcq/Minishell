/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:43:53 by mael              #+#    #+#             */
/*   Updated: 2023/03/14 14:43:54 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	env(char **argv, t_mini_sh *mini_sh)
{
	int	j;

	if (ft_strncmp(argv[0], "env", 3) == 0)
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

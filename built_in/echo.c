/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:57:05 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/02/18 16:58:30 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_echo(char **str)
{
	int i;

	i = 0;
	if (ft_strncmp(str[1], "echo", 4) == 0)
	{
		if (!str[2])
		{
			printf("\n");
			return (SUCCESS);
		}
		if (ft_strncmp(str[2], "-n", 2) != 0)
		{		
			i = 2;
			while (str[i])
				printf("%s ", str[i++]);
			printf("\n");
		}
		else
		{
			i = 3;
			while (str[i])
				printf("%s ", str[i++]);
		}
		return (SUCCESS);
	}
	else
		printf("%s: command not found\n", str[1]);
	return (FAIL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:57:05 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/04/20 15:23:11 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int g_exit_stt;

int	ft_echo(char **str)
{
	int	i;

	i = 0;
	if (ft_strncmp(str[0], "echo", 4) == 0)
	{
		if (!str[1])
			return (printf("\n"), SUCCESS);
		if (ft_strncmp(str[1], "-n", 2) != 0)
		{		
			i = 1;
			while (str[i])
				printf("%s ", str[i++]);
			printf("\n");
		}
		else
		{
			i = 2;
			while (str[i])
				printf("%s ", str[i++]);
		}
		g_exit_stt = 0;
		return (SUCCESS);
	}
	else
		printf("%s: command not found\n", str[0]);
	return (FAIL);
}

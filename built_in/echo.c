/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:57:05 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/05/02 13:50:32 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

int	ft_echo(char **tab)
{
	int	i;

	i = 0;
	if (ft_strncmp(tab[0], "echo", 4) == 0)
	{
		if (!tab[1])
			return (printf("\n"), SUCCESS);
		if (fill_n(tab[1]) == FAIL)
		{
			i = 1;
			while (tab[i])
				printf("%s ", tab[i++]);
			printf("\n");
		}
		else
		{
			i = 2;
			while (tab[i])
				printf("%s ", tab[i++]);
		}
		g_exit_stt = 0;
		return (SUCCESS);
	}
	printf("%s: command not found\n", tab[0]);
	return (FAIL);
}

int	fill_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] != '\0')
			return (FAIL);
		return (SUCCESS);
	}
	else
		return (FAIL);
}

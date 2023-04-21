/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:54:25 by mael              #+#    #+#             */
/*   Updated: 2023/04/21 16:06:59 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

int	ft_atoi(char *str)
{
	int				i;
	int				j;
	int				sign;
	int				k;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	sign = 1;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign = sign * (-1);
		i++;
	}
	j = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		j = (j * 10) + (str[i] - '0');
		i++;
	}
	k = (j * sign);
	printf(BACK_PURPLE"j: %i"RST"\n", j);
	if (str[i] != '\0' || k > 2147483647)
		return (-1);
	return (j * sign);
}

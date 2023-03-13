/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:40:08 by gael              #+#    #+#             */
/*   Updated: 2023/03/11 19:48:21 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

// int ft_strncmp(char *str, char *dest, int n)
// {
// 	int i;

// 	i = 0;
// 	while (i < n)
// 	{
// 		if (str[i] != dest[i])
// 			return (str[i] - dest[i]);
// 		i++;
// 	}
// 	return (0);
// }

int ft_strncmp(char *str, char *dest, int n)
{
	int i;

	i = 0;
	while (str[i] && dest[i] && (str[i] == dest[i]) && i < n)
		i++;
	return (str[i] - dest[i]);
}

int ft_strcmp(char *str, char *dest)
{
	int i;

	i = 0;
	if (!str[0] && !dest[0])
		return (0);
	if (!str[0])
		return (-1);
	if (!dest[0])
		return (1);
	while (str[i] == dest[i])
		i++;
	if (!str[i])
		return (0 - dest[i]);
	if (!dest[i])
		return (0 - str[i]);
	return (str[i] - dest[i]);
}

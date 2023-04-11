/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:08:55 by gael              #+#    #+#             */
/*   Updated: 2023/04/11 16:53:00 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

char	*ft_strdup(char *str)
{
	char	*res;
	int		i;

	res = malloc(sizeof (char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strdup_len(char *str, int start, int end)
{
	char	*res;
	int		ite_str;
	int		ite_res;

	ite_res = 0;
	ite_str = 0;
	while (str[ite_str])
		ite_str++;
	if (end > ite_str)
		return (NULL);
	res = malloc(sizeof (char) * (end - start + 1));
	if (!res)
		return (NULL);
	ite_str = start;
	while (ite_str < end)
	{
		res[ite_res] = str[ite_str];
		ite_res++;
		ite_str++;
	}
	res[ite_res] = '\0';
	return (res);
}

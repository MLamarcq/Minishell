/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:43:18 by gael              #+#    #+#             */
/*   Updated: 2023/02/17 12:58:25 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_strlen(char *str)
{
	int ite = 0;

	if (!str)
		return (0);
	while (str[ite])
		ite++;
	return (ite);
}

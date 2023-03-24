/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:04:44 by gael              #+#    #+#             */
/*   Updated: 2023/03/24 15:50:12 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

t_parse	*ft_lstnew_word(char *content, int save, int ite)
{
	t_parse	*new;

	new = (t_parse *)malloc(sizeof(t_parse));
	if (!new)
		return (NULL);
	new->type = 0;
	new->word = ft_strdup_len(content, save, ite);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_parse	*ft_lstnew_malloc(int size)
{
	t_parse	*new;

	new = malloc(sizeof(t_parse));
	if (!new)
		return (NULL);
	new->word = malloc(sizeof (char) * (size + 1));
	new->next = NULL;
	return (new);
}

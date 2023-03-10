/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:27:16 by gael              #+#    #+#             */
/*   Updated: 2023/02/22 00:43:33 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

static size_t	word_count(const char *str, char sep)
{
	size_t	nbr_word;
	size_t	i_wc;

	i_wc = 0;
	nbr_word = 0;
	while (str[i_wc])
	{
		if (str[i_wc] == sep)
			i_wc++;
		if (str[i_wc] && str[i_wc] != sep)
		{
			nbr_word++;
			while (str[i_wc] && str[i_wc] != sep)
				i_wc++;
		}
	}
	return (nbr_word);
}

static size_t	word_len(const char *str, char sep, size_t	i_wl)
{
	size_t	nbr_char;

	nbr_char = 0;
	while (str[i_wl] && str[i_wl] != sep)
	{
		i_wl++;
		nbr_char++;
	}
	return (nbr_char);
}

static void	declaration(size_t *i, size_t *t)
{
	*i = 0;
	*t = -1;
}

static void	jump_sep(size_t *i_ins, size_t *i, const char *str, char sep)
{
	*i_ins = 0;
	while (str[*i] && str[*i] == sep)
		(*i)++;
}

char	**ft_split(const char *str, char sep)
{
	char	**tab;
	size_t	t;
	size_t	i;
	size_t	i_ins;

	declaration(&i, &t);
	tab = (char **)malloc(sizeof(char *) * (word_count(str, sep) + 1));
	if (!tab)
		return (NULL);
	while (++t < word_count(str, sep))
	{
		jump_sep(&i_ins, &i, str, sep);
		if (str[i] && str[i] != sep)
		{
			tab[t] = (char *)malloc((word_len(str, sep, i) + 1) * sizeof(char));
			if (!tab[t])
				return (ft_free_all(NULL, tab), NULL);
			while (str[i] && str[i] != sep)
				tab[t][i_ins++] = str[i++];
			tab[t][i_ins] = '\0';
		}
	}
	tab[t] = 0;
	return (tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_wo_qt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:13:00 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/23 22:31:13 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	first_part(char *str, int *i_start, int *i_end, int *i_act)
{
	*i_start = (*i_act);
	while (str[(*i_act)] && (str[(*i_act)] != D_QUOTE \
	&& str[(*i_act)] != S_QUOTE))
		(*i_act)++;
	*i_end = (*i_act);
}

void	second_part(char *str, int *last_qt, int *i_act)
{
	*last_qt = str[(*i_act)];
	if (str[(*i_act)])
		(*i_act)++;
}

void	repeat_part(char **str_wo_qt, char *str, int i_start, int i_end)
{
	if ((*str_wo_qt) == NULL)
		(*str_wo_qt) = ft_strdup_len(str, i_start, i_end);
	else
		(*str_wo_qt) = ft_strjoin_dfree((*str_wo_qt), \
		ft_strdup_len(str, i_start, i_end));
}

void	last_part(char *str, int *i_start, int *i_act, int last_qt)
{
	*i_start = (*i_act);
	while (str[(*i_act)] && str[(*i_act)] != last_qt)
		(*i_act)++;
}

char	*write_without_qt_2(char *str)
{
	char	*str_wo_qt;
	int		i_act;
	int		last_qt;
	int		i_start;
	int		i_end;

	i_end = 0;
	i_start = 0;
	last_qt = 0;
	i_act = 0;
	str_wo_qt = NULL;
	while (str[i_act])
	{
		first_part(str, &i_start, &i_end, &i_act);
		second_part(str, &last_qt, &i_act);
		repeat_part(&str_wo_qt, str, i_start, i_end);
		last_part(str, &i_start, &i_act, last_qt);
		i_end = i_act;
		repeat_part(&str_wo_qt, str, i_start, i_end);
		if (str[i_act])
			i_act++;
	}
	if (str_wo_qt == NULL)
		str_wo_qt = str;
	return (str_wo_qt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:19:01 by gael              #+#    #+#             */
/*   Updated: 2023/04/14 11:22:31 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

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
		i_start = i_act;
		while (str[i_act] && (str[i_act] != D_QUOTE && str[i_act] != S_QUOTE))
			i_act++;
		i_end = i_act;
		last_qt = str[i_act];
		if (str[i_act])
			i_act++;
		if (str_wo_qt == NULL)
			str_wo_qt = ft_strdup_len(str, i_start, i_end);
		else
			str_wo_qt = ft_strjoin_dfree(str_wo_qt, \
			ft_strdup_len(str, i_start, i_end));
		i_start = i_act;
		while (str[i_act] && str[i_act] != last_qt)
			i_act++;
		i_end = i_act;
		if (str_wo_qt == NULL)
			str_wo_qt = ft_strdup_len(str, i_start, i_end);
		else
			str_wo_qt = ft_strjoin_dfree(str_wo_qt, \
			ft_strdup_len(str, i_start, i_end));
		if (str[i_act])
			i_act++;
	}
	if (str_wo_qt == NULL)
		str_wo_qt = str;
	(void)last_qt;
	return (str_wo_qt);
}

int	isthere_quote(t_mini_sh *mini_sh)
{
	int	i_isthereqt;

	i_isthereqt = 0;
	while (mini_sh->rl_out->word[i_isthereqt])
	{
		if (mini_sh->rl_out->word[i_isthereqt] == D_QUOTE
			|| mini_sh->rl_out->word[i_isthereqt] == S_QUOTE)
			return (SUCCESS);
		i_isthereqt++;
	}
	return (FAIL);
}

void	remove_quote_2(t_mini_sh *mini_sh)
{
	t_mini_sh	*mini_tmp;
	char		*save;

	mini_tmp = mini_sh;
	mini_tmp->rl_out = mini_sh->rl_out_head;
	while (mini_tmp->rl_out)
	{
		if (isthere_quote(mini_sh) == SUCCESS)
		{
			save = ft_strdup(mini_tmp->rl_out->word);
			free(mini_tmp->rl_out->word);
			mini_tmp->rl_out->word = write_without_qt_2(save);
			free(save);
		}
		mini_tmp->rl_out = mini_sh->rl_out->next;
	}
	(void)save;
}


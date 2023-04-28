/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hrdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:06:05 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/28 17:31:50 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

int	hrdoc_ft_isthere_dollar(t_mini_sh *mini_sh, char *word, int *i_isdollar)
{
	int	rtn_val;

	rtn_val = FAIL;
	while (word[++(*i_isdollar)])
	{
		toggle_quote(mini_sh, word[(*i_isdollar)]);
		if ((mini_sh->is_dquote == SUCCESS || (mini_sh->is_dquote == FAIL && \
		mini_sh->is_squote == FAIL)) && word[(*i_isdollar)] \
		!= '"' && word[(*i_isdollar)] != '\'')
		{
			if (word[(*i_isdollar)] == '$' \
			&& (valid_id(word[(*i_isdollar) + 1]) == SUCCESS))
			{
				rtn_val = (*i_isdollar);
				break ;
			}
		}
	}
	return (rtn_val);
}

void	hrdoc_exit_code(char **word)
{
	int		i_ecode;
	int		save;
	char	*tmp;

	i_ecode = -1;
	save = FAIL;
	while ((*word)[++i_ecode])
	{
		if ((*word)[i_ecode] == '$' \
		&& (*word)[i_ecode + 1] == '?')
		{
			save = i_ecode;
			break ;
		}
	}
	if (save != FAIL)
	{
		tmp = ft_strdup_len((*word), 0, save);
		tmp = ft_strjoin_dfree(tmp, ft_itoa(g_exit_stt));
		tmp = ft_strjoin_dfree(tmp, ft_strdup_len((*word), \
		save + 2, ft_strlen((*word))));
		free((*word));
		(*word) = ft_strdup(tmp);
		free(tmp);
	}
}

void	hrdoc_expand(t_mini_sh *mini_sh, char **word)
{
	int		i_dollar;
	int		save;

	save = FAIL;
	i_dollar = FAIL;
	init_quote(mini_sh);
	i_dollar = hrdoc_ft_isthere_dollar(mini_sh, *word, &i_dollar);
	save = i_dollar;
	while (i_dollar != -1)
	{
		save = i_dollar;
		hrdoc_replace_dollar(mini_sh, word, &i_dollar);
		i_dollar = save;
		i_dollar--;
		i_dollar = hrdoc_ft_isthere_dollar(mini_sh, *word, &i_dollar);
	}
	hrdoc_exit_code(word);
}

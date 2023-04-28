/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 02:21:41 by gael              #+#    #+#             */
/*   Updated: 2023/04/28 12:19:16 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

int	ft_isthere_dollar(t_mini_sh *mini_sh, int *i_isdollar)
{
	int	rtn_val;

	rtn_val = FAIL;
	while (mini_sh->rl_out->word[++(*i_isdollar)])
	{
		toggle_quote(mini_sh, mini_sh->rl_out->word[(*i_isdollar)]);
		if ((mini_sh->is_dquote == SUCCESS || (mini_sh->is_dquote == FAIL && \
		mini_sh->is_squote == FAIL)) && mini_sh->rl_out->word[(*i_isdollar)] \
		!= '"' && mini_sh->rl_out->word[(*i_isdollar)] != '\'')
		{
			if (mini_sh->rl_out->word[(*i_isdollar)] == '$' \
			&& (valid_id(mini_sh->rl_out->word[(*i_isdollar) + 1]) == SUCCESS))
			{
				rtn_val = (*i_isdollar);
				break ;
			}
		}
	}
	return (rtn_val);
}

void	toggle_quote(t_mini_sh *mini_sh, char chr)
{
	if (chr == S_QUOTE)
	{
		if (mini_sh->is_squote == FAIL)
			mini_sh->is_squote = SUCCESS;
		else
			mini_sh->is_squote = FAIL;
	}
	else if (chr == D_QUOTE && mini_sh->is_squote == FAIL)
	{
		if (mini_sh->is_dquote == FAIL)
			mini_sh->is_dquote = SUCCESS;
		else
			mini_sh->is_dquote = FAIL;
	}
}

void	exit_code(t_mini_sh *mini_sh)
{
	int		i_ecode;
	int		save;
	char	*tmp;

	i_ecode = -1;
	save = FAIL;
	while (mini_sh->rl_out->word[++i_ecode])
	{
		if (mini_sh->rl_out->word[i_ecode] == '$' \
		&& mini_sh->rl_out->word[i_ecode + 1] == '?')
		{
			save = i_ecode;
			break ;
		}
	}
	if (save != FAIL)
	{
		tmp = ft_strdup_len(mini_sh->rl_out->word, 0, save);
		tmp = ft_strjoin_dfree(tmp, ft_itoa(g_exit_stt));
		tmp = ft_strjoin_dfree(tmp, ft_strdup_len(mini_sh->rl_out->word, \
		save + 2, ft_strlen(mini_sh->rl_out->word)));
		free(mini_sh->rl_out->word);
		mini_sh->rl_out->word = ft_strdup(tmp);
		free(tmp);
	}
}

void	expand(t_mini_sh *mini_sh)
{
	int		i_dollar;
	int		save;
	char	*dest;

	save = FAIL;
	dest = NULL;
	i_dollar = FAIL;
	mini_sh->rl_out = mini_sh->rl_out_head;
	while (mini_sh->rl_out)
	{
		init_quote(mini_sh);
		i_dollar = ft_isthere_dollar(mini_sh, &i_dollar);
		save = i_dollar;
		if (ft_strncmp(mini_sh->rl_out->word, "<<", \
		ft_strlen(mini_sh->rl_out->word)) == 0)
		dest = ft_strdup(mini_sh->rl_out->word);
		inside_expand(mini_sh, &save, &i_dollar, dest);
		if (dest != NULL)
		{
			free(dest);
			dest = NULL;
		}
	}
	if (dest != NULL)
	{
		free(dest);
		dest = NULL;
	}
}

void	inside_expand(t_mini_sh *mini_sh, int *save, int *i_dollar, char *dest)
{
	while ((*i_dollar) != -1 && !dest)
	{
		(*save) = (*i_dollar);
		replace_dollar(mini_sh, i_dollar);
		(*i_dollar) = (*save);
		(*i_dollar)--;
		(*i_dollar) = ft_isthere_dollar(mini_sh, i_dollar);
	}
	exit_code(mini_sh);
	mini_sh->rl_out = mini_sh->rl_out->next;
}

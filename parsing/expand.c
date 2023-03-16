/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 02:21:41 by gael              #+#    #+#             */
/*   Updated: 2023/03/16 14:17:32 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

// int	len_word_replace(int end1, int start2, int end2)
// {
	
// }

void	replace_dollar(t_mini_sh * mini_sh, int *i_replace)
{
	int		save;
	int		save2;
	char	*var_name;
	char	*final_var;

	final_var = 0;
	save = 0;
	save2 = 0;
	save = (*i_replace);

	if (mini_sh->rl_out->word[(*i_replace)] == '$')
		(*i_replace)++;
	while (mini_sh->rl_out->word[(*i_replace)] && valid_id(mini_sh->rl_out->word[(*i_replace)]) == SUCCESS)
		(*i_replace)++;
	save2 = (*i_replace);
	var_name = ft_strdup_len(mini_sh->rl_out->word, (save + 1), (*i_replace));
	final_var = ft_find_var_env(mini_sh->env, var_name);
	free(var_name);
	if (final_var)
		final_var = ft_strjoin_dfree(ft_strdup_len(mini_sh->rl_out->word, 0, save), final_var);
	else
		final_var = ft_strdup_len(mini_sh->rl_out->word, 0, save);

	while (mini_sh->rl_out->word[(*i_replace)])
		(*i_replace)++;
	final_var = ft_strjoin_dfree(final_var, ft_strdup_len(mini_sh->rl_out->word, save2, (*i_replace)));
	free(mini_sh->rl_out->word);
	mini_sh->rl_out->word = ft_strdup(final_var);
	free(final_var);
	(void)save2;
	(void)var_name;
	(void)mini_sh;
}

int	interpreted(t_mini_sh *mini_sh)
{
	int	i_isdollar;

	i_isdollar = -1;
	while (mini_sh->rl_out->word[++i_isdollar])
	{
		toggle_quote(mini_sh, mini_sh->rl_out->word[i_isdollar]);
		if ((mini_sh->is_dquote == SUCCESS || (mini_sh->is_dquote == FAIL && mini_sh->is_squote == FAIL)) && mini_sh->rl_out->word[i_isdollar] != '"' && mini_sh->rl_out->word[i_isdollar] != '\'')
		{
			replace_dollar(mini_sh, &i_isdollar);
			break ;
		}
	}
	return (SUCCESS);
	(void)i_isdollar;
	(void)mini_sh;
}

int	ft_isthere_dollar(t_mini_sh *mini_sh)
{
	int	i_isdollar;
	int	rtn_val;

	rtn_val = FAIL;
	i_isdollar = -1;
	while (mini_sh->rl_out->word[++i_isdollar])
	{
		toggle_quote(mini_sh, mini_sh->rl_out->word[i_isdollar]);
		if ((mini_sh->is_dquote == SUCCESS || (mini_sh->is_dquote == FAIL && mini_sh->is_squote == FAIL)) && mini_sh->rl_out->word[i_isdollar] != '"' && mini_sh->rl_out->word[i_isdollar] != '\'')
		{
			if (mini_sh->rl_out->word[i_isdollar] == '$' && (valid_id(mini_sh->rl_out->word[i_isdollar + 1]) == SUCCESS))
			{
				rtn_val = i_isdollar;
			}
		}
	}
	return (rtn_val);
	(void)i_isdollar;
	(void)mini_sh;
}

void	init_quote(t_mini_sh *mini_sh)
{
	mini_sh->is_squote = FAIL;
	mini_sh->is_dquote = FAIL;
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

void	expand(t_mini_sh *mini_sh)
{
	int	i_dollar;

	i_dollar = FAIL;
	mini_sh->rl_out = mini_sh->rl_out_head;
	while (mini_sh->rl_out)
	{
		init_quote(mini_sh);
		i_dollar = ft_isthere_dollar(mini_sh);
		while (i_dollar != -1)
		{
			init_quote(mini_sh);
			replace_dollar(mini_sh, &i_dollar);
			// interpreted(mini_sh);
			init_quote(mini_sh);
			i_dollar = ft_isthere_dollar(mini_sh);
		}
		mini_sh->rl_out = mini_sh->rl_out->next;
	}
}

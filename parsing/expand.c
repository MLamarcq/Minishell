/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 02:21:41 by gael              #+#    #+#             */
/*   Updated: 2023/04/10 18:07:01 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	replace_dollar(t_mini_sh *mini_sh, int *i_replace)
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
	// printf(BOLD_GREEN"%p: "GREEN"%s"RESET"\n", var_name, var_name);
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
	// printf(BOLD_YELLOW"%p: "YELLOW"%s"RESET"\n", mini_sh->rl_out->word, mini_sh->rl_out->word);
	free(final_var);
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
	(void)i_isdollar;
	(void)mini_sh;
	return (SUCCESS);
}
// echo $$$USER$
int	ft_isthere_dollar(t_mini_sh *mini_sh, int *i_isdollar)
{
	int	rtn_val;

	rtn_val = FAIL;
	while (mini_sh->rl_out->word[++(*i_isdollar)])
	{

		// printf(YELLOW"%c: %i"RESET"\n", mini_sh->rl_out->word[(*i_isdollar)], (*i_isdollar));
		toggle_quote(mini_sh, mini_sh->rl_out->word[(*i_isdollar)]);
		if ((mini_sh->is_dquote == SUCCESS || (mini_sh->is_dquote == FAIL && \
		mini_sh->is_squote == FAIL)) && mini_sh->rl_out->word[(*i_isdollar)] \
		!= '"' && mini_sh->rl_out->word[(*i_isdollar)] != '\'')
		{
			if (mini_sh->rl_out->word[(*i_isdollar)] == '$' && (valid_id(mini_sh->rl_out->word[(*i_isdollar) + 1]) == SUCCESS))
			{
				// printf(BOLD_PURPLE"->%c: "PURPLE"%i"RESET"\n", mini_sh->rl_out->word[(*i_isdollar) + 1], valid_id(mini_sh->rl_out->word[(*i_isdollar) + 1]));
				rtn_val = (*i_isdollar);
				break ;
			}
		}
	}
	// printf("---------------------------\n");
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

void	expand(t_mini_sh *mini_sh)
{
	int	i_dollar;
	int	save;

	save = FAIL;
	i_dollar = FAIL;
	// i_dollar = ft_isthere_dollar(mini_sh, &i_dollar);
	mini_sh->rl_out = mini_sh->rl_out_head;
	while (mini_sh->rl_out)
	{
		init_quote(mini_sh);
		i_dollar = ft_isthere_dollar(mini_sh, &i_dollar);
		save = i_dollar;
		while (i_dollar != -1)
		{
			init_quote(mini_sh);
			// printf(BOLD_GREEN"%p: "GREEN"%s"RESET"\n", mini_sh->rl_out->word, mini_sh->rl_out->word);
			save = i_dollar;
			replace_dollar(mini_sh, &i_dollar);
			i_dollar = save;
			i_dollar--;
			// printf(BOLD_RED"%c: "RED"%i"RESET"\n", mini_sh->rl_out->word[(i_dollar) + 1], valid_id(mini_sh->rl_out->word[(i_dollar) + 1]));
			// interpreted(mini_sh);
			init_quote(mini_sh);
			i_dollar = ft_isthere_dollar(mini_sh, &i_dollar);
		}
		mini_sh->rl_out = mini_sh->rl_out->next;
	}
}

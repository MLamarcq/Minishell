/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:38:32 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/23 16:56:33 by ggosse           ###   ########.fr       */
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
	start_replace_dlr(mini_sh, i_replace, &save, &save2);
	var_name = ft_strdup_len(mini_sh->rl_out->word, (save + 1), (*i_replace));
	final_var = ft_find_var_env(mini_sh->env, var_name);
	free(var_name);
	if (final_var)
		final_var = ft_strjoin_dfree(ft_strdup_len(mini_sh->rl_out->word, \
		0, save), final_var);
	else
		final_var = ft_strdup_len(mini_sh->rl_out->word, 0, save);
	while (mini_sh->rl_out->word[(*i_replace)])
		(*i_replace)++;
	final_var = ft_strjoin_dfree(final_var, \
	ft_strdup_len(mini_sh->rl_out->word, save2, (*i_replace)));
	free(mini_sh->rl_out->word);
	mini_sh->rl_out->word = ft_strdup(final_var);
	free(final_var);
}

void	start_replace_dlr(t_mini_sh *mn_sh, int *i_rplc, int *save, int *save2)
{
	*save = (*i_rplc);
	if (mn_sh->rl_out->word[(*i_rplc)] == '$')
		(*i_rplc)++;
	while (mn_sh->rl_out->word[(*i_rplc)] \
	&& valid_id(mn_sh->rl_out->word[(*i_rplc)]) == SUCCESS)
		(*i_rplc)++;
	*save2 = (*i_rplc);
}

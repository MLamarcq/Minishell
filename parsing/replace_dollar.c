/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:38:32 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/28 15:23:44 by mlamarcq         ###   ########.fr       */
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
	start_rplc_dlr(mini_sh, &save, &save2, i_replace);
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

void	start_rplc_dlr(t_mini_sh *mini_sh, int *save, int *save2, int *i_rplc)
{
	*save = (*i_rplc);
	if (mini_sh->rl_out->word[(*i_rplc)] == '$')
		(*i_rplc)++;
	while (mini_sh->rl_out->word[(*i_rplc)] \
	&& valid_id(mini_sh->rl_out->word[(*i_rplc)]) == SUCCESS)
		(*i_rplc)++;
	*save2 = (*i_rplc);
}

void	free_dest_expand(char **dest)
{
	if ((*dest) != NULL)
	{
		free((*dest));
		(*dest) = NULL;
	}
}

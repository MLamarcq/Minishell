/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hrdoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:58:35 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/23 23:20:13 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	hrdoc_replace_dollar(t_mini_sh *mini_sh, char **word, int *i_replace)
{
	int		save;
	int		save2;
	char	*var_name;
	char	*final_var;

	final_var = 0;
	save = 0;
	save2 = 0;
	hrdoc_start_rplc_dlr(word, &save, &save2, i_replace);
	var_name = ft_strdup_len((*word), (save + 1), (*i_replace));
	final_var = ft_find_var_env(mini_sh->env, var_name);
	free(var_name);
	if (final_var)
		final_var = ft_strjoin_dfree(ft_strdup_len((*word), \
		0, save), final_var);
	else
		final_var = ft_strdup_len((*word), 0, save);
	while ((*word)[(*i_replace)])
		(*i_replace)++;
	final_var = ft_strjoin_dfree(final_var, \
	ft_strdup_len((*word), save2, (*i_replace)));
	free((*word));
	(*word) = ft_strdup(final_var);
	free(final_var);
}

void	hrdoc_start_rplc_dlr(char **word, int *sv, int *sv2, int *i_rplc)
{
	*sv = (*i_rplc);
	if ((*word)[(*i_rplc)] == '$')
		(*i_rplc)++;
	while ((*word)[(*i_rplc)] && valid_id((*word)[(*i_rplc)]) == SUCCESS)
		(*i_rplc)++;
	*sv2 = (*i_rplc);
}

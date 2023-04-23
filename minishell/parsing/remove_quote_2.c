/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:19:01 by gael              #+#    #+#             */
/*   Updated: 2023/04/23 22:42:19 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:06:13 by mael              #+#    #+#             */
/*   Updated: 2023/05/02 11:38:25 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	fill_little_tab(t_mini_sh *mini_sh, int trple)
{
	int	dble;

	dble = 0;
	mini_sh->nbr_word = 0;
	while (mini_sh->rl_out && is_sep_int(mini_sh->rl_out->type) == FAIL)
	{
		mini_sh->prepare_exec[trple][dble] = ft_strdup(mini_sh->rl_out->word);
		dble++;
		if (!mini_sh->rl_out->next)
			break ;
		else
			mini_sh->rl_out = mini_sh->rl_out->next;
	}
	mini_sh->prepare_exec[trple][dble] = NULL;
}

int	init_big_tab(t_mini_sh *mini_sh)
{
	mini_sh->rl_out = mini_sh->rl_out_head;
	if (count_sep_2(mini_sh) == FAIL)
		return (FAIL);
	mini_sh->prepare_exec = (char ***)malloc((sizeof (char **)) * \
	(mini_sh->sep_2 + 2));
	if (!mini_sh->prepare_exec)
		return (FAIL_MALLOC);
	if (is_sep_int(mini_sh->rl_out->type) == SUCCESS)
		mini_sh->rl_out = mini_sh->rl_out->next;
	return (SUCCESS);
}

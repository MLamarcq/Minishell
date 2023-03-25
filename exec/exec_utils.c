/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:06:13 by mael              #+#    #+#             */
/*   Updated: 2023/03/25 14:35:22 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	fill_little_tab(t_mini_sh *mini_sh, int trple)
{
	int	dble;

	dble = 0;
	mini_sh->nbr_word = 0;
	while (mini_sh->rl_out && is_sep(mini_sh->rl_out->word) == FAIL)
	{
		mini_sh->prepare_exec[trple][dble] = ft_strdup(mini_sh->rl_out->word);
		dble++;
		// if (mini_sh->rl_out->prev && mini_sh->rl_out->prev->type == HR_DOC)
		// {
		// 	break ;
		// }
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
	// printf("nb sep = %d\n", mini_sh->sep_2);
	//if_hr_doc(mini_sh);
	//printf(YELLOW"nbr_sep = %d"RST"\n", mini_sh->sep_2);
	mini_sh->prepare_exec = (char ***)malloc((sizeof (char **)) * \
	(mini_sh->sep_2 + 2));
	if (!mini_sh->prepare_exec)
		return (FAIL_MALLOC);
	if (is_sep(mini_sh->rl_out->word) == SUCCESS)
		mini_sh->rl_out = mini_sh->rl_out->next;
	return (SUCCESS);
}

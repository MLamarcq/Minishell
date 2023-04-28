/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:38:57 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/04/28 16:14:21 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	set_index(t_mini_sh *mini_sh)
{
	int	index;

	index = 0;
	mini_sh->rl_out = mini_sh->rl_out_head;
	mini_sh->rl_out->index = 0;
	while (mini_sh->rl_out)
	{
		mini_sh->rl_out->index = index;
		index++;
		if (mini_sh->rl_out->type == PIPE)
			index = 0;
		mini_sh->rl_out = mini_sh->rl_out->next;
	}
}

void	all_glue(t_mini_sh *mini_sh)
{
	glue_pipe(mini_sh);
	glue_hrdoc(mini_sh);
	glue_app(mini_sh);
	glue_redirr(mini_sh);
	glue_redirl(mini_sh);
}

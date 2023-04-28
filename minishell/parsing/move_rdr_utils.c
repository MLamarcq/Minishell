/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rdr_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:13:31 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/04/28 15:48:11 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	move_last(t_mini_sh *mini, t_parse *temp, t_parse *tmp, t_parse *tmp_3)
{
	tmp = mini->rl_out->prev;
	temp = mini->rl_out->next;
	if (mini->rl_out->prev && mini->rl_out->prev->prev)
		tmp_3 = mini->rl_out->prev->prev;
	mini->rl_out->next = tmp;
	mini->rl_out->prev = tmp->prev;
	tmp->prev = mini->rl_out;
	tmp->next = temp;
	temp->prev = tmp;
	if (mini->rl_out->prev && mini->rl_out->prev->prev)
		tmp_3->next = mini->rl_out;
	while (mini->rl_out->prev)
		mini->rl_out = mini->rl_out->prev;
	mini->rl_out_head = mini->rl_out;
}

void	move_middle(t_mini_sh *mini_sh)
{
	mini_sh->tmp = mini_sh->rl_out->prev;
	mini_sh->temp = mini_sh->rl_out->prev->prev;
	if (mini_sh->rl_out->next)
		mini_sh->tmp_2 = mini_sh->rl_out->next;
	if (mini_sh->rl_out->prev && mini_sh->rl_out->prev->prev \
	&& mini_sh->rl_out->prev->prev->prev)
		mini_sh->tmp_3 = mini_sh->rl_out->prev->prev->prev;
	mini_sh->tmp->next = mini_sh->rl_out->next;
	mini_sh->rl_out->next = mini_sh->tmp;
	mini_sh->tmp->prev = mini_sh->rl_out;
	mini_sh->temp->next = mini_sh->rl_out;
	mini_sh->rl_out->prev = mini_sh->temp;
	if (mini_sh->rl_out->next && mini_sh->tmp_2)
	{
		mini_sh->tmp->next = mini_sh->tmp_2;
		mini_sh->tmp_2->prev = mini_sh->tmp;
	}
	if (mini_sh->rl_out->prev && mini_sh->rl_out->prev->prev \
	&& mini_sh->rl_out->prev->prev->prev)
	{
		mini_sh->tmp_3->next = mini_sh->temp;
		mini_sh->temp->prev = mini_sh->tmp_3;
	}
}

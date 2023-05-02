/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rdr_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:53:35 by ggosse            #+#    #+#             */
/*   Updated: 2023/05/02 10:21:51 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	move_1(t_mini_sh *mini_sh)
{
	mini_sh->temp = NULL;
	mini_sh->tmp = NULL;
	mini_sh->tmp_2 = NULL;
	mini_sh->tmp_3 = NULL;
	if (case_1(mini_sh) == FAIL)
		return (FAIL);
	while (mini_sh->rl_out->next && (mini_sh->rl_out->type != CMD \
	&& mini_sh->rl_out->type != CMD_ABS))
		mini_sh->rl_out = mini_sh->rl_out->next;
	if (mini_sh->rl_out->index != 0 && mini_sh->rl_out->index != 1)
		move_middle(mini_sh);
	else if (mini_sh->rl_out->index == 1)
		move_last(mini_sh, mini_sh->temp, mini_sh->tmp, mini_sh->tmp_3);
	if (case_1(mini_sh) == SUCCESS)
		move_1(mini_sh);
	return (SUCCESS);
}

int	move_2(t_mini_sh *mini_sh)
{
	t_parse	*temp;
	t_parse	*tmp;
	t_parse	*tmp_2;

	temp = NULL;
	tmp = NULL;
	tmp_2 = NULL;
	if (case_2(mini_sh) == FAIL)
		return (FAIL);
	while (mini_sh->rl_out->next && mini_sh->rl_out->type != OPTION)
		mini_sh->rl_out = mini_sh->rl_out->next;
	if (mini_sh->rl_out->index != 0 && mini_sh->rl_out->index != 1)
		move_2_3(mini_sh, tmp, temp, tmp_2);
	if (case_2(mini_sh) == SUCCESS)
		move_2(mini_sh);
	return (SUCCESS);
}

int	move_3(t_mini_sh *mini_sh)
{
	t_parse	*temp;
	t_parse	*tmp;
	t_parse	*tmp_2;

	temp = NULL;
	tmp = NULL;
	tmp_2 = NULL;
	if (case_3(mini_sh) == FAIL)
		return (FAIL);
	while (mini_sh->rl_out->next && mini_sh->rl_out->type != ARG)
		mini_sh->rl_out = mini_sh->rl_out->next;
	if (mini_sh->rl_out->index != 0 && mini_sh->rl_out->index != 1)
		move_2_3(mini_sh, tmp, temp, tmp_2);
	if (case_3(mini_sh) == SUCCESS)
		move_3(mini_sh);
	return (SUCCESS);
}

void	move_2_3(t_mini_sh *mini, t_parse *tmp, t_parse *temp, t_parse *tmp_2)
{
	tmp = mini->rl_out;
	while (tmp && tmp->type != CMD && tmp->type != CMD_ABS)
		tmp = tmp->prev;
	if (tmp)
		temp = tmp->next;
	if (mini->rl_out)
		tmp_2 = mini->rl_out->prev;
	if (tmp_2 && mini->rl_out)
		tmp_2->next = mini->rl_out->next;
	if (mini->rl_out->next)
		mini->rl_out->next->prev = mini->rl_out->next->prev->prev;
	if (mini->rl_out)
		mini->rl_out->next = temp;
	if (temp)
		temp->prev = mini->rl_out;
	if (tmp)
		tmp->next = mini->rl_out;
	if (mini->rl_out)
		mini->rl_out->prev = tmp;
}

void	all_move(t_mini_sh *mini_sh)
{
	move_1(mini_sh);
	// ft_print_rl_out(mini_sh);
	move_2(mini_sh);
	// printf("\n.....................................\n\n");
	// ft_print_rl_out(mini_sh);
	move_3(mini_sh);
}
// < main.c /usr/bin/cat -e

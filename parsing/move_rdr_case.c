/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rdr_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:04:55 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/04/28 16:11:57 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	case_1(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	set_index(mini_sh);
	mini_sh->rl_out = mini_sh->rl_out_head;
	while (mini_sh->rl_out)
	{
		if (is_all(mini_sh->rl_out->type) == SUCCESS)
		{
			tmp = mini_sh->rl_out->next;
			while (tmp && is_sep_int(tmp->type) == FAIL)
			{
				if (tmp->type == CMD || tmp->type == CMD_ABS)
					return (SUCCESS);
				tmp = tmp->next;
			}
		}
		mini_sh->rl_out = mini_sh->rl_out->next;
	}
	return (FAIL);
}

int	case_2(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	set_index(mini_sh);
	mini_sh->rl_out = mini_sh->rl_out_head;
	while (mini_sh->rl_out)
	{
		if (is_all(mini_sh->rl_out->type) == SUCCESS)
		{
			tmp = mini_sh->rl_out->next;
			while (tmp && is_sep_int(tmp->type) == FAIL)
			{
				if (tmp->type == OPTION)
					return (SUCCESS);
				tmp = tmp->next;
			}
		}
		mini_sh->rl_out = mini_sh->rl_out->next;
	}
	return (FAIL);
}

int	case_3(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	set_index(mini_sh);
	mini_sh->rl_out = mini_sh->rl_out_head;
	while (mini_sh->rl_out)
	{
		if (is_all(mini_sh->rl_out->type) == SUCCESS)
		{
			tmp = mini_sh->rl_out->next;
			while (tmp && is_sep_int(tmp->type) == FAIL)
			{
				if (tmp->type == ARG && tmp->prev && tmp->prev->prev && \
				is_all(tmp->prev->prev->type) == SUCCESS)
					return (SUCCESS);
				tmp = tmp->next;
			}
		}
		mini_sh->rl_out = mini_sh->rl_out->next;
	}
	return (FAIL);
}

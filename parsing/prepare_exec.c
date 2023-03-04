/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:52:27 by gael              #+#    #+#             */
/*   Updated: 2023/02/26 17:56:23 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	count_double_arr(t_mini_sh *mini_sh)
{
	t_mini_sh	*mn_tmp;
	int	len_double_arr;

	len_double_arr = 0;
	mn_tmp = mini_sh;
	mn_tmp->rl_out = mini_sh->rl_out_head;
	while (mn_tmp->rl_out)
	{
		if (mn_tmp->rl_out->type == PIPE)
			len_double_arr++;
		mn_tmp->rl_out = mn_tmp->rl_out->next;
	}
	return (len_double_arr);
}

void	prepare_exec(t_mini_sh *mini_sh)
{
	printf(BACK_PURPLE"count_double_arr(mini_sh): %i"RST"\n", count_double_arr(mini_sh));
}

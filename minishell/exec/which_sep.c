/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_sep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:29:33 by mael              #+#    #+#             */
/*   Updated: 2023/05/02 15:10:17 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	init_exec(t_mini_sh *mini_sh)
{
	mini_sh->exec = malloc(sizeof(t_exec_t));
	if (!mini_sh->exec)
		return (FAIL_MALLOC);
	mini_sh->exec->ana_l = 0;
	mini_sh->exec->ana_r = 0;
	mini_sh->exec->ana_app = 0;
	mini_sh->exec->ana_hr = 0;
	mini_sh->exec->nbr_fd_r = 0;
	mini_sh->exec->nbr_fd_l = 0;
	mini_sh->exec->nbr_fd_hr = 0;
	mini_sh->exec->nbr_fd_app = 0;
	mini_sh->exec->check_r = 0;
	mini_sh->exec->check_l = 0;
	mini_sh->exec->check_hr = 0;
	mini_sh->exec->check_app = 0;
	init_exec_2(mini_sh);
	return (SUCCESS);
}

void	init_exec_2(t_mini_sh *mini_sh)
{
	mini_sh->exec->already_l = 0;
	mini_sh->exec->already_hr = 0;
	mini_sh->exec->fd_hr = 0;
	mini_sh->exec->fd_app = 0;
	mini_sh->exec->fd_l = 0;
	mini_sh->exec->fd_r = 0;
	mini_sh->exec->hr_name = NULL;
	mini_sh->exec->tab_fd = NULL;
	mini_sh->exec->fd_in = 0;
	mini_sh->exec->fd_out = 1;
}

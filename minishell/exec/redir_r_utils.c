/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_r_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:00:33 by gael              #+#    #+#             */
/*   Updated: 2023/05/02 07:35:31 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	do_redir_r(t_mini_sh *mini_sh, int i_exec)
{
	if (mini_sh->sep_2 != 0)
	{
		close(mini_sh->exec->tab_fd[i_exec][1]);
		close(mini_sh->exec->tab_fd[i_exec][0]);
	}
	mini_sh->exec->fd_out = mini_sh->exec->fd_r[mini_sh->exec->check_r];
}

void	free_redir_r(t_mini_sh *mini_sh)
{
	if (mini_sh->exec->nbr_fd_r > 0)
		free(mini_sh->exec->fd_r);
}

int	init_fail_rtab(t_mini_sh *mini_sh, int *i)
{
	mini_sh->exec->fd_r = malloc(sizeof(int) * mini_sh->exec->nbr_fd_r + 1);
	if (!mini_sh->exec->fd_r)
		return (FAIL_MALLOC);
	(*i) = -1;
	while (++(*i) < mini_sh->exec->nbr_fd_r)
		mini_sh->exec->fd_r[(*i)] = FAIL;
	(*i) = -1;
	return (SUCCESS);
}

int	init_fail_ltab(t_mini_sh *mini_sh, int *i)
{
	mini_sh->exec->fd_l = malloc(sizeof(int) * mini_sh->exec->nbr_fd_l + 1);
	if (!mini_sh->exec->fd_l)
		return (FAIL_MALLOC);
	(*i) = -1;
	while (++(*i) < mini_sh->exec->nbr_fd_l)
		mini_sh->exec->fd_l[(*i)] = FAIL;
	(*i) = -1;
	return (SUCCESS);
}

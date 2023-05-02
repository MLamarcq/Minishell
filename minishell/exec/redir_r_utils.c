/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_r_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:00:33 by gael              #+#    #+#             */
/*   Updated: 2023/05/02 11:31:10 by mlamarcq         ###   ########.fr       */
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

int	change_nbr_r_util(t_mini_sh *mini_sh, t_parse *temp, int *check)
{
	if (is_sep_int(temp->type) == SUCCESS)
	{
		if (temp->type == REDIR_R)
			(*check) = 1;
		if ((*check) == 1)
			mini_sh->exec->nbr_fd_r = mini_sh->exec->nbr_fd_r - 1;

		return (SUCCESS);
	}
	return (FAIL);
}

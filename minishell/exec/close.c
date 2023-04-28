/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:18:41 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/04/28 17:24:22 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	close_pipe(t_mini_sh *mini_sh, int i)
{
	if (mini_sh->exec->tab_fd && mini_sh->exec->tab_fd[i] \
	&& mini_sh->exec->tab_fd[i][0] > 2)
		close(mini_sh->exec->tab_fd[i][0]);
	if (mini_sh->exec->tab_fd && mini_sh->exec->tab_fd[i] \
	&& mini_sh->exec->tab_fd[i][1] > 2)
		close(mini_sh->exec->tab_fd[i][1]);
}

void	close_rdr(int *tab_rdr, int nbr_rdr)
{
	int	i_cls_rdr;

	i_cls_rdr = -1;
	while (++i_cls_rdr < nbr_rdr)
	{
		if (tab_rdr[i_cls_rdr] > 2 && tab_rdr[i_cls_rdr] < 1024)
			close(tab_rdr[i_cls_rdr]);
	}
}

void	close_all(t_mini_sh *mini_sh)
{
	int	i;

	i = 0;
	if (mini_sh->redir_alone == SUCCESS)
		close_pipe(mini_sh, i);
	else
	{
		if (first_is_a_redir(mini_sh) == SUCCESS)
			close_pipe(mini_sh, i);
		while (i < mini_sh->sep_2 + 1)
		{
			close_pipe(mini_sh, i);
			i++;
		}
	}
	if (mini_sh->exec->nbr_fd_r > 0)
		close_rdr(mini_sh->exec->fd_r, mini_sh->exec->nbr_fd_r);
	if (mini_sh->exec->nbr_fd_l > 0)
		close_rdr(mini_sh->exec->fd_l, mini_sh->exec->nbr_fd_l);
	if (mini_sh->exec->nbr_fd_hr > 0)
		close_rdr(mini_sh->exec->fd_hr, mini_sh->exec->nbr_fd_hr);
	if (mini_sh->exec->nbr_fd_app > 0)
		close_rdr(mini_sh->exec->fd_app, mini_sh->exec->nbr_fd_app);
}

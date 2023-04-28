/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:55:23 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/28 21:53:35 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

void	ft_parent(t_mini_sh *mini_sh, int *i_exec)
{
	int	err;

	close_all(mini_sh);
	(*i_exec) = 0;
	while (mini_sh->prepare_exec[(*i_exec)] && mini_sh->pids \
	&& mini_sh->pids[(*i_exec)] && mini_sh->pids[(*i_exec)] != FAIL)
	{
		if (mini_sh->pids[(*i_exec)] != FAIL)
			waitpid(mini_sh->pids[(*i_exec)], &g_exit_stt, 0);
		if (WIFEXITED(g_exit_stt))
		{
			err = WEXITSTATUS(g_exit_stt);
			g_exit_stt = err;
		}
		else if (WIFSIGNALED(g_exit_stt))
			g_exit_stt = 128 + WTERMSIG(g_exit_stt);
		if (g_exit_stt == 131)
			write(1, "Quit (core dumped)\n", 19);
		(*i_exec)++;
	}
	if (mini_sh->exec->nbr_fd_hr > 0)
		unlink_hr_dc(mini_sh);
	exec_signal(1);
}

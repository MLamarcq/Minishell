/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:55:23 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/22 17:44:26 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

void	exit_status(t_mini_sh *mini_sh, int i_exec)
{
	int	err;

	while (mini_sh->prepare_exec[i_exec])
	{
		// printf("g_exit_stt : %d\n", g_exit_stt);
		if (mini_sh->pids[i_exec] != FAIL)
			waitpid(mini_sh->pids[i_exec], &g_exit_stt, 0);
		// printf("start  err : %d\n", g_exit_stt);
		if (WIFEXITED(g_exit_stt))
		{
			//err = WIFEXITED(g_exit_stt);
			// printf("bef err : %d\n", g_exit_stt);
			err = WEXITSTATUS(g_exit_stt);
			// printf("aft err : %d\n", err);
			g_exit_stt = err;
			// fprintf(stderr, "mini_sh->prepare_exec[%i][0] = %s\n", i_exec, mini_sh->prepare_exec[i_exec][0]);
			// printf("exit_stt : %d\n", g_exit_stt);
		}
		i_exec++;
	}
}

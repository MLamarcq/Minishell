/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:07:31 by mael              #+#    #+#             */
/*   Updated: 2023/04/20 18:39:42 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int g_exit_stt;

void	exec_signal(int index)
{
	if (index == 1)
	{
		signal(SIGINT, &handle_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (index == 2)
	{
		// signal(SIGINT, SIG_IGN);
		// signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handle_sigint_2);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	handle_sigint_2(int sig)
{
	g_exit_stt += sig;
	if (sig == 2)
	{
		printf("--->X<---");
		g_exit_stt = 130;
		printf("g = %d\n", g_exit_stt);
		write(1, "\n", 2);
		rl_replace_line("", 0);
		rl_redisplay();
		//signal(SIGINT, SIG_DFL);
		 exit(130);
	}
}

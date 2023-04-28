/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:07:31 by mael              #+#    #+#             */
/*   Updated: 2023/04/28 11:49:17 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

void	exec_signal(int index)
{
	if (index == 1)
	{
		//g_exit_stt = 130;
		signal(SIGINT, &handle_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (index == 2)
	{
		signal(SIGINT, &handle_sigint_2);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (index == 3)
	{
		//g_exit_stt = 130;
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (index == 4)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, &handle_sigquit);
	}
}

void	handle_sigquit(int sig)
{
	g_exit_stt += sig;
	if (sig == 3)
	{
		g_exit_stt = 131;
		rl_replace_line("", 0);
		rl_redisplay();
		exit (131);
	}
}

void	handle_sigint_2(int sig)
{
	g_exit_stt += sig;
	if (sig == 2)
	{
		g_exit_stt = 130;
		write(1, "\n", 2);
		rl_replace_line("", 0);
		rl_redisplay();
		//exit(130);
		//return ;
		close(0);
	}
}

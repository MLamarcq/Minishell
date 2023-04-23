/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:07:31 by mael              #+#    #+#             */
/*   Updated: 2023/04/23 20:17:48 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

void	exec_signal(int index)
{
	if (index == 1)
	{
		signal(SIGINT, &handle_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (index == 2)
	{
		signal(SIGINT, &handle_sigint_2);
		signal(SIGQUIT, SIG_IGN);
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
		exit(130);
	}
}

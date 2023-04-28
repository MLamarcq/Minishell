/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:28:22 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/04/28 17:42:59 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

void	end_exec_cmd(t_mini_sh *mini_sh)
{
	g_exit_stt = 0;
	close_all(mini_sh);
	free_all(mini_sh);
	exit (0);
}

void	print_cmd_not_found(t_mini_sh *mini_sh, int i_exec)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(mini_sh->prepare_exec[i_exec][0], 2);
	ft_putstr_fd(": command not found\n", 2);
	close_all(mini_sh);
	free_all(mini_sh);
	exit (127);
}

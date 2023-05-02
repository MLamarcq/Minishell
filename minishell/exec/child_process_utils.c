/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:28:22 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/05/02 17:39:12 by mlamarcq         ###   ########.fr       */
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

void	cmd_not_found(t_mini_sh *mini_sh, int i_exec)
{
	t_parse	*tmp;

	tmp = NULL;
	if (i_exec > 0 && mini_sh->sep_type && mini_sh->sep_type[i_exec - 1] \
	&& mini_sh->sep_type[i_exec - 1] != PIPE)
		end_exec_cmd(mini_sh);
	else if (i_exec == 0 && is_there_a_redir(mini_sh) == SUCCESS)
		end_exec_cmd(mini_sh);
	else
	{
		tmp = mini_sh->rl_out_head;
		while (tmp->next)
			tmp = tmp->next;
		if (tmp->prev && issep_read(tmp->prev->type) == SUCCESS)
			end_exec_cmd(mini_sh);
		print_cmd_not_found(mini_sh, i_exec);
	}
}

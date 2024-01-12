/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:02:23 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/05/03 11:12:14 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	go_to_last_read_3(t_mini_sh *mini_sh, int i_exec)
{
	int	i_last_read;
	int	check;

	i_last_read = i_exec;
	check = 0;
	while (mini_sh->sep_type[i_last_read] && \
	(issep_write(mini_sh->sep_type[i_last_read]) == FAIL && \
	mini_sh->sep_type[i_last_read] != PIPE && \
	mini_sh->sep_type[i_last_read] != FAIL) && (i_last_read < (mini_sh->sep_2)))
	{
		if (issep_read(mini_sh->sep_type[i_last_read]) == SUCCESS)
			check = 1;
		i_last_read++;
	}
	if (middle_last_read_2(mini_sh, i_last_read, check) == FAIL)
		return ;
}

int	middle_last_read_2(t_mini_sh *mini_sh, int i_last_read, int check)
{
	if (check == 1)
	{
		if (mini_sh->sep_type && mini_sh->sep_type[i_last_read] \
		&& mini_sh->sep_type[i_last_read] == REDIR_L)
			mini_sh->exec->fd_in = mini_sh->exec->fd_l[mini_sh->exec->check_l];
		else if (mini_sh->sep_type && mini_sh->sep_type[i_last_read] \
		&& mini_sh->sep_type[i_last_read] == HR_DOC && \
		mini_sh->exec->fd_hr[i_last_read])
		{
			if (mini_sh->exec->fd_hr[i_last_read])
				close (mini_sh->exec->fd_hr[i_last_read]);
			mini_sh->exec->fd_hr[i_last_read] = \
			open(mini_sh->exec->hr_name[i_last_read], O_RDONLY, 0644);
			if (!mini_sh->exec->hr_name[i_last_read])
				return (FAIL);
			mini_sh->exec->fd_in = mini_sh->exec->fd_hr[i_last_read];
		}
	}
	return (SUCCESS);
}

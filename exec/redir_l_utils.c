/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_l_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:34:03 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/05/03 10:52:31 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	free_redir_l(t_mini_sh *mini_sh)
{
	if (mini_sh->exec->nbr_fd_l > 0)
		free(mini_sh->exec->fd_l);
}

int	do_good_redir_l(t_mini_sh *mini_sh, int i_exec)
{
	int	i;

	i = i_exec;
	if (i == mini_sh->sep_2 - 1)
		return (FAIL);
	while (mini_sh->sep_type && mini_sh->sep_type[i] && i < mini_sh->sep_2)
	{
		if (mini_sh->sep_type[i] != REDIR_L && mini_sh->sep_type[i] != HR_DOC)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

void	do_redir_l(t_mini_sh *mini_sh, int i_exec)
{
	if (mini_sh->sep_2 && mini_sh->sep_type && \
	(mini_sh->sep_2 == 1 || !mini_sh->sep_type[i_exec + 1]))
		close(mini_sh->exec->tab_fd[i_exec][1]);
	mini_sh->exec->fd_in = mini_sh->exec->fd_l[mini_sh->exec->check_l];
	if (mini_sh->sep_type && do_good_redir_l(mini_sh, i_exec) \
	== SUCCESS && one_hr_multi_l(mini_sh) == FAIL)
	{
		go_to_last_read_2(mini_sh, i_exec);
		mini_sh->exec->fd_out = 1;
	}
	else if (mini_sh->sep_type[i_exec + 1] \
	&& mini_sh->sep_type[i_exec + 1] != FAIL)
		do_good_redir(mini_sh, i_exec);
	else
	{
		close(mini_sh->exec->tab_fd[i_exec][1]);
		mini_sh->exec->fd_out = 1;
	}
}

void	do_good_redir(t_mini_sh *mini_sh, int i_exec)
{
	int	i;

	i = i_exec;
	while (mini_sh->sep_type && mini_sh->sep_type[i] != FAIL && \
	(mini_sh->sep_type[i] != PIPE && mini_sh->sep_type[i] != REDIR_R \
	&& mini_sh->sep_type[i] != APPEND))
		i++;
	if (mini_sh->sep_type[i] == PIPE)
		mini_sh->exec->fd_out = mini_sh->exec->tab_fd[i][1];
	else if (mini_sh->sep_type[i] == REDIR_R)
		mini_sh->exec->fd_out = mini_sh->exec->fd_r[mini_sh->exec->check_r];
	else if (mini_sh->sep_type[i] == APPEND)
		mini_sh->exec->fd_out = \
		mini_sh->exec->fd_app[mini_sh->exec->check_app];
}

int	check_last_read(t_mini_sh *mini_sh, int i_last_read, int check, int i)
{
	if (check == 1)
	{
		if (i_last_read < mini_sh->sep_2 && mini_sh->sep_type \
		&& mini_sh->sep_type[i_last_read - 1] \
		&& mini_sh->sep_type[i_last_read - 1] == \
		REDIR_L && mini_sh->exec->fd_l[i_last_read - 1])
		mini_sh->exec->fd_in = mini_sh->exec->fd_l[i_last_read - 1];
		else if (mini_sh->sep_type && mini_sh->sep_type[i_last_read - 1] \
		&& mini_sh->sep_type[i_last_read - 1] == HR_DOC)
		{
			close (mini_sh->exec->fd_hr[mini_sh->exec->check_hr + i]);
			mini_sh->exec->fd_hr[mini_sh->exec->check_hr + i] = \
			open(mini_sh->exec->hr_name[mini_sh->exec->check_hr + i], \
			O_RDONLY, 0644);
			if (!mini_sh->exec->hr_name[mini_sh->exec->check_hr + i])
				return (FAIL);
			mini_sh->exec->fd_in = \
			mini_sh->exec->fd_hr[mini_sh->exec->check_hr + i];
		}
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:55:56 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/05/03 11:11:16 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	go_to_last_read(t_mini_sh *mini_sh, int i_exec)
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
	if (middle_last_read(mini_sh, i_last_read, check) == FAIL)
		return ;
}

void	one_l_multi_hr_util(t_parse *tmp, int *hr_check)
{
	while (tmp)
	{
		if (tmp->type == HR_DOC && tmp->next && \
		tmp->next->next && tmp->next->next->type == HR_DOC)
		{
			(*hr_check) = SUCCESS;
			break ;
		}
		tmp = tmp->next;
	}
}

void	do_heredoc_redir(t_mini_sh *mini_sh, int i_exec)
{
	close (mini_sh->exec->fd_hr[mini_sh->exec->check_hr]);
	mini_sh->exec->fd_hr[mini_sh->exec->check_hr] = \
	open(mini_sh->exec->hr_name[mini_sh->exec->check_hr], O_RDONLY, 0644);
	if (mini_sh->sep_2 && mini_sh->sep_type && \
	(mini_sh->sep_2 == 1 || !mini_sh->sep_type[i_exec + 1]))
		close(mini_sh->exec->tab_fd[i_exec][1]);
	mini_sh->exec->fd_in = mini_sh->exec->fd_hr[mini_sh->exec->check_hr];
	if (mini_sh->sep_type && do_good_redir_l(mini_sh, \
	i_exec) == SUCCESS && one_l_multi_hr(mini_sh) == FAIL)
	{
		go_to_last_read(mini_sh, i_exec);
		mini_sh->exec->fd_out = 1;
	}
	else if (mini_sh->sep_type[i_exec + 1] && \
	mini_sh->sep_type[i_exec + 1] != FAIL)
	{
		go_to_last_read_3(mini_sh, i_exec);
		do_good_redir(mini_sh, i_exec);
	}
	else
	{
		close(mini_sh->exec->tab_fd[i_exec][1]);
		mini_sh->exec->fd_out = 1;
	}
}

void	unlink_hr_dc(t_mini_sh *mini_sh)
{
	int	i;

	i = 0;
	while (i < mini_sh->exec->nbr_fd_hr)
	{
		unlink(mini_sh->exec->hr_name[i]);
		i++;
	}
}

void	free_hr_doc(t_mini_sh *mini_sh)
{
	if (mini_sh->exec->nbr_fd_hr > 0)
		free(mini_sh->exec->fd_hr);
}

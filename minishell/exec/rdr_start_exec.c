/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_start_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:22:20 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/05/02 15:22:59 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	exec_redir(t_mini_sh *mini, int i_exec)
{
	if (i_exec < mini->sep_2 && mini->sep_type \
	&& mini->sep_type[i_exec] != FAIL && mini->sep_type[i_exec] == REDIR_R)
		do_redir_r(mini, i_exec);
	else if (i_exec < mini->sep_2 && mini->sep_type \
	&& mini->sep_type[i_exec] != FAIL && mini->sep_type[i_exec] == APPEND)
		do_append(mini, i_exec);
	else if (i_exec < mini->sep_2 && mini->sep_type \
	&& mini->sep_type[i_exec] != FAIL && mini->sep_type[i_exec] == HR_DOC)
		do_heredoc_redir(mini, i_exec);
	else if (i_exec < mini->sep_2 && mini->sep_type \
	&& mini->sep_type[i_exec] != FAIL && mini->sep_type[i_exec] == REDIR_L)
		do_redir_l(mini, i_exec);
	return (SUCCESS);
}

int	is_there_a_redir(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type && is_sep_int(tmp->type) == SUCCESS && tmp->type != PIPE)
			return (SUCCESS);
		tmp = tmp->next;
	}
	return (FAIL);
}

int	first_is_a_redir(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	if (is_all(tmp->type) == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

int	count_redir_in_line(t_mini_sh *mini_sh, int type)
{
	t_parse	*temp;

	while (mini_sh->rl_check_redir)
	{
		if (mini_sh->rl_check_redir->type == type)
		{
			temp = mini_sh->rl_check_redir->next;
			while (temp)
			{
				if (is_sep_int(temp->type) == SUCCESS)
				{
					if (temp->type == type)
						return (SUCCESS);
					else
						return (FAIL);
				}
				temp = temp->next;
			}
		}
		mini_sh->rl_check_redir = mini_sh->rl_check_redir->next;
	}
	return (SUCCESS);
}

void	increase_check(t_mini_sh *mini_sh, int type)
{
	if (type == REDIR_R)
	{
		if (mini_sh->exec->check_r < mini_sh->exec->nbr_fd_r && \
		count_redir_in_line(mini_sh, type) == FAIL)
			mini_sh->exec->check_r++;
	}
	else if (type == APPEND)
	{
		if (mini_sh->exec->check_app < mini_sh->exec->nbr_fd_app && \
		count_redir_in_line(mini_sh, type) == FAIL)
			mini_sh->exec->check_app++;
	}
	else if (type == HR_DOC)
	{
		if (mini_sh->exec->check_hr < mini_sh->exec->nbr_fd_hr && \
		count_redir_in_line(mini_sh, type) == FAIL)
			mini_sh->exec->check_hr++;
	}
	else if (type == REDIR_L)
	{
		if (mini_sh->exec->check_l < mini_sh->exec->nbr_fd_l && \
		count_redir_in_line(mini_sh, type) == FAIL)
			mini_sh->exec->check_l++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:58:05 by ggosse            #+#    #+#             */
/*   Updated: 2023/05/02 08:16:33 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	analyse_redir_before_alloc(t_mini_sh *mini_sh, t_parse *tmp)
{
	t_parse	*temp;

	temp = tmp;
	if (temp->type == RDR_R)
	{
		temp = temp->next;
		while (temp)
		{
			if (temp->type == RDR_R)
			{
				mini_sh->exec->ana_r = 1;
				break ;
			}
			else if (temp->type == PIPE)
			{
				mini_sh->exec->ana_r = 0;
				break ;
			}
			temp = temp->next;
		}
	}
}

void	when_append_after(t_mini_sh *mini_sh, int i)
{
	t_parse	*tmp;
	t_parse	*temp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == RDR_R)
		{
			temp = tmp;
			while (temp)
			{
				if (temp->type == APPEND)
				{
					mini_sh->exec->fd_r[i] = \
					mini_sh->exec->fd_app[mini_sh->exec->check_app];
					mini_sh->count_redir_r = 1;
				}
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
}

void	change_nbr_r(t_mini_sh *mini_sh)
{
	int		check;
	t_parse	*tmp;
	t_parse	*temp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		check = 0;
		if (tmp->type == RDR_R)
		{
			temp = tmp->next;
			while (temp)
			{
				if (change_nbr_r_util(mini_sh, temp, &check) == SUCCESS)
					break ;
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
}

int	init_redir_r_tab(t_mini_sh *mini_sh)
{
	int		i;
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	if (mini_sh->exec->nbr_fd_r == 0)
		return (FAIL);
	change_nbr_r(mini_sh);
	init_fail_rtab(mini_sh, &i);
	while (++i < mini_sh->exec->nbr_fd_r)
	{
		while (tmp)
		{
			if (tmp->type == RDR_R)
			{
				init_redir_r_util(mini_sh, tmp, i);
				tmp = tmp->next;
				if (mini_sh->exec->ana_r == 0)
					break ;
			}
			tmp = tmp->next;
		}
	}
	return (SUCCESS);
}

int	init_redir_r_util(t_mini_sh *mini_sh, t_parse *tmp, int i)
{
	analyse_redir_before_alloc(mini_sh, tmp);
	if (mini_sh->exec->fd_r[i] != FAIL)
		close(mini_sh->exec->fd_r[i]);
	mini_sh->exec->fd_r[i] = \
	open(tmp->next->word, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (mini_sh->exec->fd_r[i] == -1)
		return (FAIL);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:33:12 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/05/02 11:31:52 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	change_nbr_append_util(t_mini_sh *mini_sh, t_parse *temp, int *check)
{
	if (is_sep_int(temp->type) == SUCCESS)
	{
		if (temp->type == APPEND)
			(*check) = 1;
		if ((*check) == 1)
			mini_sh->exec->nbr_fd_app = mini_sh->exec->nbr_fd_app - 1;
		return (SUCCESS);
	}
	return (FAIL);
}

int	init_append_tab_util(t_mini_sh *mini_sh, t_parse *tmp, int *i)
{
	if (tmp->type == APPEND)
	{
		analyse_append_before_alloc(mini_sh, tmp);
		if (mini_sh->exec->fd_app[(*i)] != FAIL)
			close(mini_sh->exec->fd_app[(*i)]);
		mini_sh->exec->fd_app[(*i)] = open(tmp->next->word, \
		O_CREAT | O_APPEND | O_RDWR, 0644);
		if (mini_sh->exec->fd_app[(*i)] == -1)
			return (FAIL);
		tmp = tmp->next;
		when_redir_r_after(mini_sh, (*i));
		when_append_after(mini_sh, (*i));
		if (mini_sh->exec->ana_app == 0)
			return (-42);
	}
	return (SUCCESS);
}

void	do_append(t_mini_sh *mini_sh, int i_exec)
{
	if (mini_sh->sep_2 != 0)
		close(mini_sh->exec->tab_fd[i_exec][1]);
	if (mini_sh->count_redir_r == 1)
		close(mini_sh->exec->fd_r[mini_sh->exec->check_r]);
	mini_sh->exec->fd_out = mini_sh->exec->fd_app[mini_sh->exec->check_app];
}

void	free_append(t_mini_sh *mini_sh)
{
	if (mini_sh->exec->nbr_fd_app > 0)
		free(mini_sh->exec->fd_app);
}

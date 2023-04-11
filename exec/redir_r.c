/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:58:05 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/11 16:58:40 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	analyse_redir_before_alloc(t_mini_sh *mini_sh, t_parse *tmp)
{
	t_parse *temp;

	temp = tmp;
	if (temp->type == REDIR_R)
	{
		temp = temp->next;
		while (temp)
		{
			if (temp->type == REDIR_R || temp->type == APPEND)
			{
				printf(RED"ici"RST"\n");
				mini_sh->exec->ana_r = 1;
				break ;
			}
			else if (temp->type == PIPE)
			{
				printf(RED"la"RST"\n");
				mini_sh->exec->ana_r = 0;
				break;
			}
			temp = temp->next;
		}
	}
}

int	init_redir_r_tab(t_mini_sh *mini_sh)
{
	int i;
	t_parse *tmp;

	tmp = mini_sh->rl_out_head;
	i = 0;
	if (mini_sh->exec->nbr_fd_r == 0)
		return (FAIL);
	mini_sh->exec->fd_r = malloc(sizeof(int) * mini_sh->exec->nbr_fd_r + 1);
	if (!mini_sh->exec->fd_r)
		return (FAIL_MALLOC);
	mini_sh->exec->fd_r[mini_sh->exec->nbr_fd_r] = 0;
	while (i < mini_sh->exec->nbr_fd_r)
	{
		while (tmp)
		{
			if (tmp->type == REDIR_R)
			{
				analyse_redir_before_alloc(mini_sh, tmp);
				mini_sh->exec->fd_r[i] = open(tmp->next->word, O_CREAT | O_TRUNC | O_RDWR, 0644);
				printf(GREEN"fd_r[%i] == %d\t%s"RST"\n", i, mini_sh->exec->fd_r[i], tmp->next->word);
				if (mini_sh->exec->fd_r[i] == -1)
					return (FAIL);
				tmp = tmp->next;
				if (mini_sh->exec->ana_r == 0)
					break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (SUCCESS);
}

void	do_redir_r(t_mini_sh *mini_sh, int i_exec)
{
	if (mini_sh->sep_2 != 0)
	{
		close(mini_sh->exec->tab_fd[i_exec][1]);
		close(mini_sh->exec->tab_fd[i_exec][0]);
	}
	if (mini_sh->sep_type[i_exec - 1] && mini_sh->sep_type[i_exec - 1] == REDIR_R)
		mini_sh->exec->fd_in = 0;
	mini_sh->exec->fd_out = mini_sh->exec->fd_r[mini_sh->exec->check_r];
}

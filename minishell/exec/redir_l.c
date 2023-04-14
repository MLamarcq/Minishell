/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:56:38 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/14 11:33:14 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	start_init_ltab(t_mini_sh *mini_sh)
{
	if (mini_sh->exec->nbr_fd_l == 0)
		return (FAIL);
	mini_sh->exec->fd_l = malloc(sizeof(int) * mini_sh->exec->nbr_fd_l + 1);
	if (!mini_sh->exec->fd_l)
		return (FAIL_MALLOC);
	mini_sh->exec->fd_l[mini_sh->exec->nbr_fd_l] = 0;
	return (1);
}

int	init_redir_l_tab(t_mini_sh *mini_sh)
{
	int		i;
	t_parse	*tmp;

	i = 0;
	tmp = mini_sh->rl_out_head;
	if (start_init_ltab(mini_sh) != SUCCESS)
		return (FAIL);
	while (i < mini_sh->exec->nbr_fd_l)
	{
		while (tmp)
		{
			if (tmp->type == REDIR_L)
			{
				mini_sh->exec->fd_l[i] = open(tmp->next->word, O_RDONLY, 0644);
				if (mini_sh->exec->fd_l[i] == -1)
					return (printf("something wrong happened\n"), FAIL);
				tmp = tmp->next;
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (SUCCESS);
}

void	do_redir_l(t_mini_sh *mini_sh, int i_exec)
{
	printf(RED"i_exec inside redir = %d"RST"\n", i_exec);
	if (mini_sh->sep_2 == 1)
	{
		printf(RED"tab_fd_l_out = %d"RST"\n", mini_sh->exec->tab_fd[i_exec][1]);
		close(mini_sh->exec->tab_fd[i_exec][1]);
	}
	mini_sh->exec->fd_in = mini_sh->exec->fd_l[mini_sh->exec->check_l];
	if (mini_sh->sep_type[i_exec + 1])
	{
		if (mini_sh->sep_type[i_exec + 1] == PIPE)
			mini_sh->exec->fd_out = mini_sh->exec->tab_fd[i_exec + 1][1];
		else if (mini_sh->sep_type[i_exec + 1] == REDIR_R)
			mini_sh->exec->fd_out = mini_sh->exec->fd_r[mini_sh->exec->check_r];
		else if (mini_sh->sep_type[i_exec + 1] == APPEND)
			mini_sh->exec->fd_out = mini_sh->exec->fd_app[mini_sh->exec->check_app];
	}
}

void	free_redir_l(t_mini_sh *mini_sh)
{
	if (mini_sh->exec->nbr_fd_l > 0)
		free(mini_sh->exec->fd_l);
}

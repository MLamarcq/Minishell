/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:56:38 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/19 12:59:02 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	analyse_redir_before_alloc_2(t_mini_sh *mini_sh, t_parse *tmp)
{
	t_parse *temp;

	temp = tmp;
	if (temp->type == REDIR_L)
	{
		temp = temp->next;
		while (temp)
		{
			if (temp->type == REDIR_L)
			{
				printf(RED"ici"RST"\n");
				mini_sh->exec->ana_l = 1;
				break ;
			}
			else if (temp->type == PIPE)
			//else
			{
				printf(RED"la"RST"\n");
				mini_sh->exec->ana_l = 0;
				break;
			}
			temp = temp->next;
		}
	}
}

void	change_nbr_l(t_mini_sh *mini_sh)
{
	int check;
	t_parse *tmp;
	t_parse *temp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		check = 0;
		if (tmp->type == REDIR_L)
		{
			temp = tmp->next;
			while (temp)
			{
				if (is_sep(temp->word) == SUCCESS)
				{
					if (temp->type == REDIR_L)
						check = 1;
					if (check == 1)
						mini_sh->exec->nbr_fd_l = mini_sh->exec->nbr_fd_l - 1;
					break ;
				}
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
}

int	init_redir_l_tab(t_mini_sh *mini_sh)
{
	int		i;
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	i = 0;
	if (mini_sh->exec->nbr_fd_l == 0)
		return (FAIL);
	change_nbr_l(mini_sh);
	mini_sh->exec->fd_l = malloc(sizeof(int) * mini_sh->exec->nbr_fd_l + 1);
	if (!mini_sh->exec->fd_l)
		return (FAIL_MALLOC);
//	mini_sh->exec->fd_l[mini_sh->exec->nbr_fd_l] = 0;
	while (i < mini_sh->exec->nbr_fd_l)
	{
		while (tmp)
		{
			if (tmp->type == REDIR_L)
			{
				analyse_redir_before_alloc_2(mini_sh, tmp);
				mini_sh->exec->fd_l[i] = open(tmp->next->word, O_RDONLY, 0644);
				if (mini_sh->exec->fd_l[i] == -1)
					return (printf("something wrong happened\n"), FAIL);
				printf(GREEN"fd_l[%i] == %d\t%s"RST"\n", i, mini_sh->exec->fd_l[i], tmp->next->word);
				tmp = tmp->next;
				if (mini_sh->exec->ana_l == 0)
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
	if (mini_sh->sep_type[i_exec + 1] == REDIR_L)
		mini_sh->exec->fd_out = 1;
	else if (mini_sh->sep_type[i_exec + 1])
	{
		if (mini_sh->sep_type[i_exec + 1] == PIPE)
			mini_sh->exec->fd_out = mini_sh->exec->tab_fd[i_exec + 1][1];
		else if (mini_sh->sep_type[i_exec + 1] == REDIR_R)
			mini_sh->exec->fd_out = mini_sh->exec->fd_r[mini_sh->exec->check_r];
		else if (mini_sh->sep_type[i_exec + 1] == APPEND)
			mini_sh->exec->fd_out = mini_sh->exec->fd_app[mini_sh->exec->check_app];
	}
	else
	{
	 	close(mini_sh->exec->tab_fd[i_exec][1]);
	 //	mini_sh->exec->fd_out = 1;
	}
}

void	free_redir_l(t_mini_sh *mini_sh)
{
	if (mini_sh->exec->nbr_fd_l > 0)
		free(mini_sh->exec->fd_l);
}

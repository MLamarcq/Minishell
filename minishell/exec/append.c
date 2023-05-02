/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:54:31 by ggosse            #+#    #+#             */
/*   Updated: 2023/05/02 14:15:46 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	analyse_append_before_alloc(t_mini_sh *mini_sh, t_parse *tmp)
{
	t_parse	*temp;

	temp = tmp;
	if (temp->type == APPEND)
	{
		temp = temp->next;
		while (temp)
		{
			if (temp->type == APPEND)
			{
				mini_sh->exec->ana_app = 1;
				break ;
			}
			else if (temp->type == PIPE)
			{
				mini_sh->exec->ana_app = 0;
				break ;
			}
			temp = temp->next;
		}
	}
}

void	when_redir_r_after(t_mini_sh *mini_sh, int i)
{
	t_parse	*tmp;
	t_parse	*temp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == APPEND)
		{
			temp = tmp;
			while (temp)
			{
				if (temp->type == REDIR_R)
				{
					mini_sh->exec->fd_app[i] = \
					mini_sh->exec->fd_r[mini_sh->exec->check_r];
				}
				else
					break ;
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
}

void	change_nbr_append(t_mini_sh *mini_sh)
{
	int		check;
	t_parse	*tmp;
	t_parse	*temp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		check = 0;
		if (tmp->type == APPEND)
		{
			temp = tmp->next;
			while (temp)
			{
				if (change_nbr_append_util(mini_sh, temp, &check) == SUCCESS)
					break ;
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
}

int	init_fd_app(t_mini_sh *mini_sh, t_parse **tmp, int *i)
{
	*tmp = mini_sh->rl_out_head;
	(*i) = -1;
	if (mini_sh->exec->nbr_fd_app == 0)
		return (FAIL);
	mini_sh->exec->fd_app = malloc(sizeof(int) * mini_sh->exec->nbr_fd_app);
	if (!mini_sh->exec->fd_app)
		return (FAIL_MALLOC);
	while (++(*i) < mini_sh->exec->nbr_fd_app)
		mini_sh->exec->fd_app[(*i)] = FAIL;
	*i = 0;
	return (SUCCESS);
}

int	init_append_tab(t_mini_sh *mini_sh)
{
	int		i;
	int		res;
	t_parse	*tmp;

	if (init_fd_app(mini_sh, &tmp, &i) < 0)
		return (FAIL);
	change_nbr_append(mini_sh);
	res = 0;
	while (i < mini_sh->exec->nbr_fd_app)
	{
		while (tmp)
		{
			res = init_append_tab_util(mini_sh, tmp, &i);
			printf("res = %d\n", res);
			if (res == FAIL)
				return (FAIL);
			if (res == -42)
				break ;
			tmp = tmp->next;
		}
		i++;
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:56:38 by ggosse            #+#    #+#             */
/*   Updated: 2023/05/02 15:17:15 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	analyse_redir_before_alloc_2(t_mini_sh *mini_sh, t_parse *tmp)
{
	t_parse	*temp;

	temp = tmp;
	if (temp->type == REDIR_L)
	{
		temp = temp->next;
		while (temp)
		{
			if (temp->type == REDIR_L)
			{
				mini_sh->exec->ana_l = 1;
				break ;
			}
			else if (temp->type == PIPE)
			{
				mini_sh->exec->ana_l = 0;
				break ;
			}
			temp = temp->next;
		}
	}
}

void	change_nbr_l(t_mini_sh *mini_sh)
{
	int		check;
	t_parse	*tmp;
	t_parse	*temp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		check = 0;
		if (tmp->type == REDIR_L)
		{
			temp = tmp->next;
			while (temp)
			{
				if (change_nbr_l_util(mini_sh, temp, &check) == SUCCESS)
					break ;
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
}

int	init_redir_l_tab(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	int		i;

	tmp = mini_sh->rl_out_head;
	if (mini_sh->exec->nbr_fd_l == 0)
		return (FAIL);
	change_nbr_l(mini_sh);
	mini_sh->exec->fd_l = malloc(sizeof(int) * mini_sh->exec->nbr_fd_l + 1);
	if (!mini_sh->exec->fd_l)
		return (FAIL_MALLOC);
	i = -1;
	while (++i < mini_sh->exec->nbr_fd_l)
		mini_sh->exec->fd_l[i] = FAIL;
	i = -1;
	while (++i < mini_sh->exec->nbr_fd_l)
	{
		if (middle_redir_l(mini_sh, tmp, i) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

int	middle_redir_l(t_mini_sh *mini_sh, t_parse *tmp, int i)
{
	while (tmp)
	{
		if (tmp->type == REDIR_L)
		{
			analyse_redir_before_alloc_2(mini_sh, tmp);
			if (mini_sh->exec->fd_l[i] != FAIL)
				close(mini_sh->exec->fd_l[i]);
			mini_sh->exec->fd_l[i] = open(tmp->next->word, O_RDONLY, 0644);
			if (mini_sh->exec->fd_l[i] == -1)
				return (printf("something wrong happened\n"), FAIL);
			tmp = tmp->next;
			if (mini_sh->exec->ana_l == 0)
				break ;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	one_hr_multi_l(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	int		l_check;
	int		hr_check;

	l_check = FAIL;
	hr_check = FAIL;
	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == HR_DOC)
		{
			l_check = SUCCESS;
			break ;
		}
		tmp = tmp->next;
	}
	rdr_l_hr_success(tmp, &hr_check);
	if (l_check == SUCCESS && hr_check == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

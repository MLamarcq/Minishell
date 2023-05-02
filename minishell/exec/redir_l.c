/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:56:38 by ggosse            #+#    #+#             */
/*   Updated: 2023/05/02 08:31:40 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	analyse_redir_before_alloc_2(t_mini_sh *mini_sh, t_parse *tmp)
{
	t_parse	*temp;

	temp = tmp;
	if (temp->type == RDR_L)
	{
		temp = temp->next;
		while (temp)
		{
			if (temp->type == RDR_L)
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
		if (tmp->type == RDR_L)
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
	init_fail_ltab(mini_sh, &i);
	while (++i < mini_sh->exec->nbr_fd_l)
	{
		while (tmp)
		{
			if (tmp->type == RDR_L)
			{
				init_redir_l_util(mini_sh, tmp, i);
				tmp = tmp->next;
				if (mini_sh->exec->ana_l == 0)
					break ;
			}
			tmp = tmp->next;
		}
	}
	return (SUCCESS);
}

int	init_redir_l_util(t_mini_sh *mini_sh, t_parse *tmp, int i)
{
	analyse_redir_before_alloc_2(mini_sh, tmp);
	if (mini_sh->exec->fd_l[i] != FAIL)
		close(mini_sh->exec->fd_l[i]);
	mini_sh->exec->fd_l[i] = open(tmp->next->word, O_RDONLY, 0644);
	if (mini_sh->exec->fd_l[i] == -1)
		return (printf("something wrong happened\n"), FAIL);
	return (SUCCESS);
}

int	one_hr_multi_l(t_mini_sh *mini_sh)
{
	t_parse	*t;
	int		l_check;
	int		hr_check;

	l_check = FAIL;
	hr_check = FAIL;
	t = mini_sh->rl_out_head;
	while (t)
	{
		if (t->type == HR_DOC)
		{
			l_check = SUCCESS;
			break ;
		}
		t = t->next;
	}
	hr_success(t, &hr_check);
	if (l_check == SUCCESS && hr_check == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

void	hr_success(t_parse *t, int *hr_check)
{
	while (t)
	{
		if (t->type == RDR_L && t->next && \
		t->next->next && t->next->next->type == RDR_L)
			(*hr_check) = SUCCESS;
		t = t->next;
	}
}

void	go_to_last_read_2(t_mini_sh *mini_sh, int i_exec)
{
	int	i_last_read;
	int	check;
	int	i;

	i = -1;
	i_last_read = i_exec;
	check = 0;
	while (mini_sh->sep_type[i_last_read] && \
	(issep_write(mini_sh->sep_type[i_last_read]) == FAIL || \
	mini_sh->sep_type[i_last_read] != FAIL || \
	mini_sh->sep_type[i_last_read] != PIPE) && (i_last_read < mini_sh->sep_2))
	{
		if (issep_read(mini_sh->sep_type[i_last_read]) == SUCCESS)
		{
			if (mini_sh->sep_type[i_last_read] == HR_DOC)
				i++;
			check = 1;
		}
		i_last_read++;
	}
	if (check_last_read(mini_sh, i_last_read, check, i) == FAIL)
		return ;
}

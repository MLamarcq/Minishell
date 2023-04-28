/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:56:38 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/28 17:55:26 by mlamarcq         ###   ########.fr       */
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
	t_parse	*tmp;
	int		i;

	tmp = mini_sh->rl_out_head;
	i = -1;
	if (mini_sh->exec->nbr_fd_l == 0)
		return (FAIL);
	change_nbr_l(mini_sh);
	mini_sh->exec->fd_l = malloc(sizeof(int) * mini_sh->exec->nbr_fd_l + 1);
	if (!mini_sh->exec->fd_l)
		return (FAIL_MALLOC);
	while (++i < mini_sh->exec->nbr_fd_l)
		mini_sh->exec->fd_l[i] = FAIL;
	i = -1;
	while (++i < mini_sh->exec->nbr_fd_l)
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
	}
	return (SUCCESS);
}

int	one_hr_multi_l(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	int	l_check;
	int	hr_check;

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
	while (tmp)
	{
		if (tmp->type == REDIR_L && tmp->next && tmp->next->next && tmp->next->next->type == REDIR_L)
			hr_check = SUCCESS;
		tmp = tmp->next;
	}
	if (l_check == SUCCESS && hr_check == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

void	go_to_last_read_2(t_mini_sh *mini_sh, int i_exec)
{
	int	i_last_read;
	int check;
	int i;

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


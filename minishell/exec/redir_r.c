/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:58:05 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/24 13:40:52 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	analyse_redir_before_alloc(t_mini_sh *mini_sh, t_parse *tmp)
{
	t_parse	*temp;

	temp = tmp;
	if (temp->type == REDIR_R)
	{
		temp = temp->next;
		while (temp)
		{
			if (temp->type == REDIR_R)
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
		if (tmp->type == REDIR_R)
		{
			temp = tmp;
			while (temp)
			{
				if (temp->type == APPEND)
				{
					mini_sh->exec->fd_r[i] = \
					mini_sh->exec->fd_app[mini_sh->exec->check_app];
				}
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
}

void	change_nbr_r(t_mini_sh *mini_sh)
{
	int check;
	t_parse *tmp;
	t_parse *temp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		check = 0;
		if (tmp->type == REDIR_R)
		{
			temp = tmp->next;
			while (temp)
			{
				if (is_sep(temp->word) == SUCCESS)
				{
					if (temp->type == REDIR_R)
						check = 1;
					if (check == 1)
						mini_sh->exec->nbr_fd_r = mini_sh->exec->nbr_fd_r - 1;
					break ;
				}
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
}

int	init_redir_r_tab(t_mini_sh *mini_sh)
{
	int i;
	t_parse *tmp;

	tmp = mini_sh->rl_out_head;
	i = 0;
	printf("nbr_redir_r = %d\n", mini_sh->exec->nbr_fd_r);
	if (mini_sh->exec->nbr_fd_r == 0)
		return (FAIL);
	change_nbr_r(mini_sh);
	printf("nbr_redir_r = %d\n", mini_sh->exec->nbr_fd_r);
	mini_sh->exec->fd_r = malloc(sizeof(int) * mini_sh->exec->nbr_fd_r + 1);
	if (!mini_sh->exec->fd_r)
		return (FAIL_MALLOC);
	// mini_sh->exec->fd_r[mini_sh->exec->nbr_fd_r] = 0;
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

void	what_is_next(t_mini_sh *mini_sh)
{
	t_parse *tmp;

	mini_sh->rl_out = mini_sh->rl_out_head;
	while (mini_sh->rl_out)
	{
		if (mini_sh->rl_out->type == REDIR_R)
		{
			tmp = mini_sh->rl_out;
			while (tmp && tmp->type != PIPE)
			{
				if (issep_read(tmp->type) == SUCCESS)
				{
					if (tmp->type == REDIR_L)
						mini_sh->exec->fd_in = mini_sh->exec->fd_l[mini_sh->exec->check_l];
					else if (tmp->type == HR_DOC)
						mini_sh->exec->fd_in = mini_sh->exec->fd_hr[mini_sh->exec->check_hr];
				}
				tmp = tmp->next;
			}
			if (tmp && tmp->type == PIPE)
				break ;
		}
		mini_sh->rl_out = mini_sh->rl_out->next;
	}
	
}


void	do_redir_r(t_mini_sh *mini_sh, int i_exec)
{
	if (mini_sh->sep_2 != 0)
	{
		close(mini_sh->exec->tab_fd[i_exec][1]);
		close(mini_sh->exec->tab_fd[i_exec][0]);
	}
	what_is_next(mini_sh);
	// if (mini_sh->sep_type[i_exec - 1] && mini_sh->sep_type[i_exec - 1] == REDIR_R)
	// 	mini_sh->exec->fd_in = 0;
	// printf(BACK_PURPLE"mini_sh->exec->fd_r[mini_sh->exec->check_r]: %i"RST"\n", mini_sh->exec->fd_r[mini_sh->exec->check_r]);
	mini_sh->exec->fd_out = mini_sh->exec->fd_r[mini_sh->exec->check_r];
}

void	free_redir_r(t_mini_sh *mini_sh)
{
	if (mini_sh->exec->nbr_fd_r > 0)
	{
			free(mini_sh->exec->fd_r);
	}
}
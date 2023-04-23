/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:54:31 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/23 22:02:53 by ggosse           ###   ########.fr       */
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
		printf("temp->word 1 = %s\n", temp->word);
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
					printf("salut\n");
					printf("before = %d\n", mini_sh->exec->fd_app[i]);
					mini_sh->exec->fd_app[i] = mini_sh->exec->fd_r[mini_sh->exec->check_r];
					printf("after = %d\n", mini_sh->exec->fd_app[i]);
				}
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
}

int	init_fd_app(t_mini_sh *mini_sh, t_parse **tmp, int *i)
{
	*tmp = mini_sh->rl_out_head;
	*i = 0;
	mini_sh->exec->fd_app = malloc(sizeof(int) * mini_sh->exec->nbr_fd_app);
	if (!mini_sh->exec->fd_app)
		return (FAIL_MALLOC);
	return (SUCCESS);
}

int	init_append_tab(t_mini_sh *mini_sh)
{
	int		i;
	t_parse	*tmp;

	init_fd_app(mini_sh, &tmp, &i);
	//mini_sh->exec->fd_app[mini_sh->exec->nbr_fd_app] = 0;
	while (i < mini_sh->exec->nbr_fd_app)
	{
		while (tmp)
		{
			if (tmp->type == APPEND)
			{
				analyse_append_before_alloc(mini_sh, tmp);
				mini_sh->exec->fd_app[i] = open(tmp->next->word, \
				O_CREAT | O_APPEND | O_RDWR, 0644);
				if (mini_sh->exec->fd_app[i] == -1)
					return (FAIL);
				tmp = tmp->next;
				when_redir_r_after(mini_sh, i);
				when_append_after(mini_sh, i);
				if (mini_sh->exec->ana_app == 0)
					break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (SUCCESS);
}

void	do_append(t_mini_sh *mini_sh, int i_exec)
{
	if (mini_sh->sep_2 != 0)
		close(mini_sh->exec->tab_fd[i_exec][1]);
	mini_sh->exec->fd_out = mini_sh->exec->fd_app[mini_sh->exec->check_app];
}

void	free_append(t_mini_sh *mini_sh)
{
	if (mini_sh->exec->nbr_fd_app > 0)
		free(mini_sh->exec->fd_app);

}

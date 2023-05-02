/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:53:46 by ggosse            #+#    #+#             */
/*   Updated: 2023/05/02 16:00:19 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	analyse_hrdoc_before_alloc(t_mini_sh *mini_sh, t_parse *tmp)
{
	t_parse	*temp;

	temp = tmp;
	if (temp->type == HR_DOC)
	{
		temp = temp->next;
		while (temp)
		{
			if (temp->type == HR_DOC)
			{
				mini_sh->exec->ana_hr = 1;
				break ;
			}
			else if (temp->type == PIPE)
			{
				mini_sh->exec->ana_hr = 0;
				break ;
			}
			temp = temp->next;
		}
	}
}

void	change_hr_doc(t_mini_sh *mini_sh)
{
	int		check;
	t_parse	*tmp;
	t_parse	*temp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		check = 0;
		if (tmp->type == HR_DOC)
		{
			temp = tmp->next;
			while (temp)
			{
				if (change_nbr_hr_util(mini_sh, temp, &check) == SUCCESS)
					break ;
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
}

int	middle_hrdoc_tab(t_mini_sh *mini_sh, t_parse *tmp, int i)
{
	while (tmp)
	{
		if (tmp->type == HR_DOC)
		{
			mini_sh->exec->hr_name[i] = \
			ft_strjoin_rfree(".heredoc", ft_itoa(i));
			mini_sh->exec->fd_hr[i] = \
			open(mini_sh->exec->hr_name[i], O_WRONLY | O_CREAT, 0644);
			if (mini_sh->exec->fd_hr[i] == -1)
				return (FAIL);
			tmp = tmp->next;
			break ;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	init_hr_dc_tab(t_mini_sh *mini_sh)
{
	int		i;
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	i = 0;
	mini_sh->exec->fd_hr = malloc(sizeof(int) * mini_sh->exec->nbr_fd_hr + 1);
	if (!mini_sh->exec->fd_hr)
		return (FAIL_MALLOC);
	mini_sh->exec->hr_name = malloc(sizeof(char *) * \
	(mini_sh->exec->nbr_fd_hr + 1));
	if (!mini_sh->exec->hr_name)
		return (FAIL_MALLOC);
	mini_sh->exec->hr_name[mini_sh->exec->nbr_fd_hr] = 0;
	while (i < mini_sh->exec->nbr_fd_hr)
	{
		if (middle_hrdoc_tab(mini_sh, tmp, i) == FAIL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	one_l_multi_hr(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	int		l_check;
	int		hr_check;

	l_check = FAIL;
	hr_check = FAIL;
	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == REDIR_L)
		{
			l_check = SUCCESS;
			break ;
		}
		tmp = tmp->next;
	}
	one_l_multi_hr_util(tmp, &hr_check);
	if (l_check == SUCCESS && hr_check == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

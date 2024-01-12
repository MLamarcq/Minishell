/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_l_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:04:11 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/05/03 10:52:07 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	rdr_l_hr_success(t_parse *tmp, int *hr_check)
{
	while (tmp)
	{
		if (tmp->type == REDIR_L && tmp->next && \
		tmp->next->next && tmp->next->next->type == REDIR_L)
			(*hr_check) = SUCCESS;
		tmp = tmp->next;
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
	(issep_write(mini_sh->sep_type[i_last_read]) == FAIL && \
	mini_sh->sep_type[i_last_read] != FAIL && \
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

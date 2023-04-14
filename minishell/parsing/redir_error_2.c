/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:50:30 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/14 11:23:10 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	redir_l_error(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == PIPE && tmp->next->type == REDIR_L)
			return (print_error(4, tmp), FAIL);
		if (tmp->type == REDIR_L)
		{
			if (opendir(tmp->next->word) != NULL)
			{
				return (printf("minishell: %s: Is a directory\n", \
				tmp->next->word), FAIL);
			}
			else if (tmp->next->type != _FILE && tmp->next->type != CMD_ABS)
			{
				return (printf("minishell: %s: No such file or directory\n", \
				tmp->next->word), FAIL);
			}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_redir_follow(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (is_sep_int(tmp->type) == SUCCESS)
		{
			if (tmp->next && is_sep_int(tmp->next->type) == SUCCESS)
				return (print_error(4, tmp), FAIL);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

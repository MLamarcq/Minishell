/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:50:30 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/28 16:12:16 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	redir_l_error(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	DIR		*dir_name;

	tmp = mini_sh->rl_out_head;
	dir_name = NULL;
	while (tmp)
	{
		if (tmp->next && tmp->type == REDIR_L)
		{
			dir_name = opendir(tmp->next->word);
			if (dir_name != NULL)
				return (closedir(dir_name), print_error(1, tmp->next), FAIL);
			else if (tmp->next->type != _FILE && tmp->next->type != CMD_ABS)
				return (closedir(dir_name), print_error(3, tmp->next), FAIL);
		}
		tmp = tmp->next;
	}
	if (dir_name != NULL)
		closedir(dir_name);
	return (SUCCESS);
}

int	redir_r_error_2(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	DIR		*dir_name;

	tmp = mini_sh->rl_out_head;
	dir_name = NULL;
	while (tmp)
	{
		if (tmp->next && (tmp->type == REDIR_R || tmp->type == APPEND))
		{
			dir_name = opendir(tmp->next->word);
			if (dir_name != NULL)
				return (closedir(dir_name), print_error(1, tmp->next), FAIL);
		}
		tmp = tmp->next;
	}
	if (dir_name != NULL)
		closedir(dir_name);
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

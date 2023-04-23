/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:00:26 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/21 18:25:22 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	check_redi_r_append_error_1(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == REDIR_R || tmp->type == APPEND)
		{
			tmp = tmp->next;
			if (opendir(tmp->word) != NULL)
			{
				if (print_error(1, tmp) == FAIL)
					return (FAIL);
			}
			if (tmp->type == _FILE || tmp->type == CMD_ABS)
			{
				if (access(tmp->word, W_OK) == -1)
				{
					if (print_error(2, tmp) == FAIL)
						return (FAIL);
				}
			}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_redi_r_append_error_2(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == REDIR_R || tmp->type == APPEND)
		{
			tmp = tmp->next;
			if ((tmp->type == _FILE && (access(tmp->word, W_OK) == 0)) \
			|| tmp->type == ARG)
			{
				if (tmp->next && (is_sep(tmp->next->word) == FAIL) \
				&& print_error(4, tmp) == FAIL)
					return (FAIL);
			}
		}
		if (tmp->type == PIPE && ((tmp->next->type == REDIR_R) \
		|| (tmp->next->type == APPEND)) && print_error(4, tmp) == FAIL)
			return (FAIL);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_redi_r_append_error(t_mini_sh *mini_sh)
{
	if (check_redir_follow(mini_sh) == FAIL)
		return (FAIL);
	else if (check_redi_r_append_error_1(mini_sh) == FAIL)
		return (FAIL);
	else if (check_redi_r_append_error_2(mini_sh) == FAIL)
		return (FAIL);
	else if (redir_l_error(mini_sh) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int print_error(int index, t_parse *tmp)
{
	if (index == 1)
	{
		printf("minishell: %s: Is a directory\n", tmp->word);
		return (FAIL);
	}
	else if (index == 2)
	{
		printf("minishell: %s: permission denied\n", tmp->word);
		return (FAIL);
	}
	else if (index == 3)
	{
		printf("%s: connot access '%s' : No such file or directory\n", \
		tmp->next->word, tmp->next->word);
		return (FAIL);
	}
	else if (index == 4)
	{
		printf("minishell: syntax error near unexpected token '%s'\n", \
		tmp->word);
		return (FAIL);
	}
	return (SUCCESS);
}

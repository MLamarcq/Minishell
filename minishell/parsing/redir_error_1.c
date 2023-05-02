/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:00:26 by ggosse            #+#    #+#             */
/*   Updated: 2023/05/02 08:16:33 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	check_redi_r_append_error_1(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	DIR		*dir_name;

	tmp = mini_sh->rl_out_head;
	dir_name = NULL;
	while (tmp)
	{
		if (tmp->next && (tmp->type == RDR_R || tmp->type == APPEND))
		{
			tmp = tmp->next;
			dir_name = opendir(tmp->word);
			if (dir_name != NULL && print_error(1, tmp) == FAIL)
				return (closedir(dir_name), FAIL);
			if (tmp->type == _FILE || access(tmp->word, X_OK) == 0)
			{
				if (access(tmp->word, W_OK) == -1)
					return (closedir(dir_name), print_error(2, tmp), FAIL);
			}
		}
		tmp = tmp->next;
	}
	if (dir_name != NULL)
		closedir(dir_name);
	return (SUCCESS);
}

int	check_redi_r_append_error_2(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == RDR_R || tmp->type == APPEND)
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
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_redi_r_append_error(t_mini_sh *mini_sh)
{
	if (check_redi_r_append_error_1(mini_sh) == FAIL)
		return (FAIL);
	else if (redir_r_error_2(mini_sh) == FAIL)
		return (FAIL);
	else if (check_redi_r_append_error_2(mini_sh) == FAIL)
		return (FAIL);
	else if (redir_l_error(mini_sh) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	print_error(int index, t_parse *tmp)
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
		tmp->word, tmp->word);
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

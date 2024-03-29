/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:00:26 by ggosse            #+#    #+#             */
/*   Updated: 2023/05/02 14:24:41 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

int	check_redi_r_append_error_1(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	DIR		*dir_name;

	tmp = mini_sh->rl_out_head;
	dir_name = NULL;
	while (tmp)
	{
		if (tmp->next && (tmp->type == REDIR_R || tmp->type == APPEND))
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
		if ((tmp->type == REDIR_R || tmp->type == APPEND) && tmp->next)
		{
			tmp = tmp->next;
			if (tmp && ((tmp->type == _FILE && (access(tmp->word, W_OK) == 0)) \
			|| tmp->type == ARG))
			{
				if (tmp->next && (is_sep_int(tmp->next->type) == FAIL) \
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
	g_exit_stt = 1;
	if (index > 2)
		g_exit_stt = 2;
	if (index == 1)
		return (printf("minishell: %s: Is a directory\n", tmp->word), FAIL);
	else if (index == 2)
		return (printf("minishell: %s: permission denied\n", tmp->word), FAIL);
	else if (index == 3)
		return (printf("%s: connot access '%s' : No such file or directory\n", \
		tmp->word, tmp->word), FAIL);
	else if (index == 4)
		return (printf("minishell: syntax error near unexpected token '%s'\n", \
		tmp->word), FAIL);
	else if (index == 5)
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		return (FAIL);
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_sep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:25:36 by gael              #+#    #+#             */
/*   Updated: 2023/04/21 18:15:24 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	check_first_is_sep(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	if (is_sep(tmp->word) == SUCCESS)
	{
		if (tmp->type == PIPE)
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			return (FAIL);
		}
		else if (tmp->type != REDIR_L && !tmp->next)
		{
			printf("minishell: syntax error near unexpected token 'newline'");
			return (FAIL);
		}
	}
	return (SUCCESS);
}

int	check_first_is_sep_2(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	if (is_sep(tmp->word) == SUCCESS)
	{
		if (tmp->type == REDIR_L)
		{
			if (tmp->next && tmp->next->type != _FILE
				&& tmp->next->type != CMD_ABS)
				return (printf("minishell: %s: No such file \
				or directory", tmp->next->word), FAIL);
			if (!tmp->next)
				return (printf("minishell: syntax error near \
				unexpected token 'newline'\n"), FAIL);
		}
	}
	return (SUCCESS);
}

int	check_first_sep_error_2(t_mini_sh *mini_sh)
{
	if (check_first_is_sep(mini_sh) == FAIL)
		return (FAIL);
	if (check_first_is_sep_2(mini_sh) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

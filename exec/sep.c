/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:25:36 by gael              #+#    #+#             */
/*   Updated: 2023/03/10 10:58:01 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	is_sep(char *word)
{
	//printf("here\n");
	if (ft_strncmp(word, "|", ft_strlen(word)) == 0)
	{
		//printf("c1\n");
		return (SUCCESS);
	}
	else if (ft_strncmp(word, ">", ft_strlen(word)) == 0)
	{
		//printf("c2\n");
		return (SUCCESS);
	}
	else if (ft_strncmp(word, "<", ft_strlen(word)) == 0)
	{
		//printf("c3\n");
		return (SUCCESS);
	}
	else if (ft_strncmp(word, ">>", ft_strlen(word)) == 0)
	{
		//printf("c4\n");
		return (SUCCESS);
	}
	else if (ft_strncmp(word, "<<", ft_strlen(word)) == 0)
	{
		//printf("c5\n");
		return (SUCCESS);
	}
	return (FAIL);
}

int	check_first_is_sep(t_mini_sh *mini_sh)
{
	t_arr_output *tmp;

	tmp = mini_sh->rl_out_head;
	if (is_sep(tmp->word) == SUCCESS)
	{
		if (tmp->type == PIPE)
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			return (FAIL);
		}
		else if (tmp->type != REDIR_L)
		{
			if (!tmp->next)
			{
				printf("minishell: syntax error near unexpected token 'newline'");
				return (FAIL);
			}
		}
	}
	return (SUCCESS);
}

int	check_first_is_sep_2(t_mini_sh *mini_sh)
{
	t_arr_output *tmp;

	tmp = mini_sh->rl_out_head;
	if (is_sep(tmp->word) == SUCCESS)
	{
		if (tmp->type == REDIR_L)
		{
			if (tmp->next && tmp->next->type != _FILE && tmp->next->type != CMD_ABS)
			{
				printf("minishell: %s: No such file or directory", tmp->next->word);
				return (FAIL);
			}
			if (!tmp->next)
			{
				printf("minishell: syntax error near unexpected token 'newline'\n");
				return (FAIL);
			}
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

int	count_sep_2(t_mini_sh *mini_sh)
{
	t_arr_output *tmp;

	tmp = mini_sh->rl_out_head;
	if (check_first_sep_error_2(mini_sh) == FAIL)
		return (FAIL);
	tmp = tmp->next;
	while (tmp && tmp->next != NULL)
	{
		if (is_sep(tmp->word) == SUCCESS)
			mini_sh->sep_2++;
		if (tmp)
			tmp = tmp->next;
	}
	if (tmp && is_sep(tmp->word) == SUCCESS)
	{
		if (tmp->type == PIPE)
		{
			printf("minishell: syntax error near unexpected token '|'");
			return (FAIL);
		}
		else
		{
			printf("minishell: syntax error near unexpected token 'newline'\n");
			return (FAIL);
		}
	}
	printf("res = %d\n", mini_sh->sep_2);
	return (SUCCESS);
}
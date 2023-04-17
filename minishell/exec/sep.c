/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:25:36 by gael              #+#    #+#             */
/*   Updated: 2023/04/17 13:00:46 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	is_sep(char *word)
{
	if (ft_strncmp(word, "|", ft_strlen(word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(word, ">", ft_strlen(word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(word, "<", ft_strlen(word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(word, ">>", ft_strlen(word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(word, "<<", ft_strlen(word)) == 0)
		return (SUCCESS);
	return (FAIL);
}

int	is_sep_int(int type)
{
	if (type == REDIR_R)
		return (SUCCESS);
	else if (type == REDIR_L)
		return (SUCCESS);
	else if (type == APPEND)
		return (SUCCESS);
	else if (type == HR_DOC)
		return (SUCCESS);
	else if (type == PIPE)
		return (SUCCESS);
	return (FAIL);
}

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

void	is_redir_alone(t_mini_sh *mini_sh)
{
	t_parse *tmp;
	
	tmp = mini_sh->rl_out_head;
	if (is_sep_int(tmp->type) == SUCCESS)
		mini_sh->redir_alone = SUCCESS;
	else
		mini_sh->redir_alone = FAIL;
}

int	count_sep_2(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	if (check_first_sep_error_2(mini_sh) == FAIL)
		return (FAIL);
	is_redir_alone(mini_sh);
	tmp = tmp->next;
	while (tmp && tmp->next != NULL)
	{
		if (is_sep(tmp->word) == SUCCESS && is_sep(tmp->next->word) == SUCCESS)
			tmp = tmp->next;
		if (is_sep(tmp->word) == SUCCESS)
			mini_sh->sep_2++;
		if (tmp)
			tmp = tmp->next;
	}
	if (tmp && is_sep(tmp->word) == SUCCESS)
	{
		if (tmp->type == PIPE)
			return (printf("minishell: syntax error near \
			unexpected token '|'"), FAIL);
		else
			return (printf("minishell: syntax error near \
			unexpected token 'newline'\n"), FAIL);
	}
	return (SUCCESS);
}

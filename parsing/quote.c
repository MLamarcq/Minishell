/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 01:53:30 by gael              #+#    #+#             */
/*   Updated: 2023/03/09 19:15:01 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"


void	count_quote_arg(char *line, int *ite, int quote)
{
	if (line[(*ite)] == quote)
	{
		(*ite)++;
		while (line[(*ite)] != quote)
			(*ite)++;
	}
}

int	count_word(char *line)
{
	int	ite;
	int	len;

	len = 0;
	ite = 0;
	while (line[ite])
	{
		while (ft_is_sep_parse(line[ite]) == SUCCESS)
			ite++;
		if (line[ite] != '\0' && ft_is_sep_parse(line[ite]) == FAIL)
			len++;
		while (line[ite] != '\0' && ft_is_sep_parse(line[ite]) == FAIL)
		{
			count_quote_arg(line, &ite, D_QUOTE);
			count_quote_arg(line, &ite, S_QUOTE);
			ite++;
		}
	}
	return (len);
}

int	quote_is_closed(char *line, int *ite, int quote)
{
	if (line[(*ite)] == quote)
	{
		(*ite)++;
		while (line[(*ite)])
		{
			if (line[(*ite)] == quote)
				return (SUCCESS);
			(*ite)++;
		}
		return (FAIL);
	}
	else
		return (SUCCESS);
}

int	check_quote_is_closed(char *line)
{
	int	ite;
	int	len;

	len = 0;
	ite = 0;
	while (line[ite])
	{
		while (ft_is_sep_parse(line[ite]) == SUCCESS)
			ite++;
		if (line[ite] != '\0' && ft_is_sep_parse(line[ite]) == FAIL)
			len++;
		while (line[ite] != '\0' && ft_is_sep_parse(line[ite]) == FAIL)
		{
			if (quote_is_closed(line, &ite, D_QUOTE) == FAIL)
				return (FAIL);
			if (quote_is_closed(line, &ite, S_QUOTE) == FAIL)
				return (FAIL);
			ite++;
		}
	}
	return (len);
}

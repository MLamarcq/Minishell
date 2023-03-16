/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:19:01 by gael              #+#    #+#             */
/*   Updated: 2023/03/16 14:36:17 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

char	*write_without_qt_2(char *str)
{
	char	*str_wo_qt;
	int		i_write;
	int		i_copy;

	str_wo_qt = malloc(sizeof (char) * (ft_strlen(str) - 1));
	str_wo_qt[(ft_strlen(str) - 1)] = '\0';
	i_write = 0;
	i_copy = 0;
	while (str[i_write])
	{
		if ((str[i_write] == S_QUOTE || str[i_write] == D_QUOTE))
			i_write++;
		else
		{
			str_wo_qt[i_copy] = str[i_write];
			i_write++;
			i_copy++;
		}
	}
	printf(BACK_GREEN"str_wo_qt: %s"RST"\n", str_wo_qt);
	return (str_wo_qt);
}

int	isthere_quote(t_mini_sh *mini_sh)
{
	int	i_isthereqt;

	i_isthereqt = 0;
	while (mini_sh->rl_out->word[i_isthereqt])
	{
		if (mini_sh->rl_out->word[i_isthereqt] == D_QUOTE
			|| mini_sh->rl_out->word[i_isthereqt] == S_QUOTE)
			return (SUCCESS);
		i_isthereqt++;
	}
	return (FAIL);
}

void	remove_quote_2(t_mini_sh *mini_sh)
{
	t_mini_sh	*mini_tmp;
	char		*save;

	mini_tmp = mini_sh;
	mini_tmp->rl_out = mini_sh->rl_out_head;
	while (mini_tmp->rl_out)
	{
		if (isthere_quote(mini_sh) == SUCCESS)
		{
			save = ft_strdup(mini_tmp->rl_out->word);
			free(mini_tmp->rl_out->word);
			mini_tmp->rl_out->word = write_without_qt_2(save);
			// free(save);
		}
		mini_tmp->rl_out = mini_sh->rl_out->next;
	}
	(void)save;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:19:01 by gael              #+#    #+#             */
/*   Updated: 2023/03/16 10:33:45 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	count_without_qt_2(char *str)
{
	int	i_str;
	int	i_real_len;

	i_real_len = 0;
	i_str = 0;
	while (str[i_str])
	{
		if (str[i_str] != '\'' && str[i_str] != '\"')
			i_real_len++;
		i_str++;
	}
	return (i_real_len);
}

char	*write_without_qt_2(char *str)
{
	char	*str_wo_qt;

	str_wo_qt = malloc(sizeof (char) * (ft_strlen(str) - 2 + 1));
	printf(BACK_GREEN"str: %s"RST"\n", str);
	return (str);
	(void)str_wo_qt;
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
		// if (isthere_quote(mini_sh) == SUCCESS)
		// {
		// 	printf(BACK_RED"->"RST"\n");
		// 	// save = ft_strdup(mini_tmp->rl_out->word);
		// 	// free(mini_tmp->rl_out->word);
		// 	// mini_tmp->rl_out->word = write_without_qt_2(save);
		// 	// free(save);
		// }
		mini_tmp->rl_out = mini_sh->rl_out->next;
	}
	(void)save;
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 23:19:01 by gael              #+#    #+#             */
/*   Updated: 2023/02/24 13:51:01 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	coun_without_qt(char *str)
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

char	*write_without_qt(char *str)
{
	int		i_str;
	int		i_real_len;
	char	*str_without_qt;

	str_without_qt = (char *)malloc((sizeof (char)) * \
	(coun_without_qt(str) + 1));
	if (!str_without_qt)
		return (NULL);
	i_real_len = 0;
	i_str = 0;
	while (str[i_str])
	{
		if (str[i_str] != '\'' && str[i_str] != '\"')
		{
			str_without_qt[i_real_len] = str[i_str];
			i_real_len++;
		}
		i_str++;
	}
	str_without_qt[i_real_len] = 0;
	return (str_without_qt);
}

void	remove_quote(t_mini_sh *mini_sh)
{
	t_mini_sh	*mini_tmp;
	char		*save;

	mini_tmp = mini_sh;
	mini_tmp->rl_out = mini_sh->rl_out_head;
	while (mini_tmp->rl_out)
	{
		save = ft_strdup(mini_tmp->rl_out->word);
		free(mini_tmp->rl_out->word);
		mini_tmp->rl_out->word = write_without_qt(save);
		free(save);
		mini_tmp->rl_out = mini_sh->rl_out->next;
	}
}



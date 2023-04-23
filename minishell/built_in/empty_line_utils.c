/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:51:25 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/23 22:51:40 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	to_empty_line_utils(t_mini_sh *mini_sh, int *len, int *j)
{
	mini_sh->data->ite_genv++;
	mini_sh->data->count++;
	(*len)++;
	(*j)++;
}

void	strcmp_empty_line(t_mini_sh *mini, char **dest, int *i, char **env_ctt)
{
	ft_bzero(mini->env[*i], ft_strlen(mini->env[*i]));
	free(*dest);
	if (*env_ctt)
		free(*env_ctt);
	*env_ctt = NULL;
}

void	end_empty_line(char **env_ctt)
{
	if (*env_ctt)
		free(*env_ctt);
	*env_ctt = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:51:25 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/28 14:55:11 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	to_empty_line_utils(t_mini_sh *mini_sh, char **argv)
{
	mini_sh->data->len = ft_strlen(argv[1]) + 1;
	mini_sh->data->dest_unset = malloc(sizeof(char) * \
	ft_strlen(mini_sh->data->env_ctt) + 1);
	if (!mini_sh->data->dest_unset)
		return (FAIL_MALLOC);
	while (mini_sh->env[mini_sh->data->i][mini_sh->data->len] \
	&& mini_sh->data->env_ctt[mini_sh->data->ite_genv] \
	&& mini_sh->env[mini_sh->data->i][mini_sh->data->len] == \
	mini_sh->data->env_ctt[mini_sh->data->ite_genv])
	{
		mini_sh->data->dest_unset[mini_sh->data->j] = \
		mini_sh->env[mini_sh->data->i][mini_sh->data->len];
		mini_sh->data->ite_genv++;
		mini_sh->data->count++;
		mini_sh->data->len++;
		mini_sh->data->j++;
	}
	return (SUCCESS);
}

int	strcmp_empty_line(t_mini_sh *mini_sh)
{
	mini_sh->data->dest_unset[mini_sh->data->j] = '\0';
	if (ft_strncmp(mini_sh->data->dest_unset, mini_sh->data->env_ctt, \
	ft_strlen(mini_sh->data->dest_unset)) == 0)
	{
		ft_bzero(mini_sh->env[mini_sh->data->i], \
		ft_strlen(mini_sh->env[mini_sh->data->i]));
		free(mini_sh->data->dest_unset);
		if (mini_sh->data->env_ctt)
			free(mini_sh->data->env_ctt);
		mini_sh->data->env_ctt = NULL;
		return (SUCCESS);
	}
	return (FAIL);
}

void	end_empty_line(t_mini_sh *mini_sh)
{
	if (mini_sh->data->env_ctt)
		free(mini_sh->data->env_ctt);
	mini_sh->data->env_ctt = NULL;
}

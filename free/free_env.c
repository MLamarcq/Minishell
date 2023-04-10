/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 19:58:25 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/03 10:31:32 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	free_data(t_mini_sh *mini_sh)
{
	if (mini_sh->data)
	{
		free_env_sorted(mini_sh);
		free(mini_sh->data);
		mini_sh->data = NULL;
	}
}

void	free_env(t_mini_sh *mini_sh)
{
	int	ite_free_env;

	ite_free_env = -1;
	if (mini_sh->env)
	{
		while (mini_sh->env[++ite_free_env])
		{
			if (mini_sh->env[ite_free_env])
			{
				free(mini_sh->env[ite_free_env]);
				mini_sh->env[ite_free_env] = NULL;
			}
		}
		free(mini_sh->env);
		mini_sh->env = NULL;
	}
}

void	free_env_sorted(t_mini_sh *mini_sh)
{
	int	ite_free_env;

	ite_free_env = -1;
	if (mini_sh->data)
	{
		if (mini_sh->data->env_sorted)
		{
			while (mini_sh->data->env_sorted[++ite_free_env])
			{
				free(mini_sh->data->env_sorted[ite_free_env]);
				mini_sh->data->env_sorted[ite_free_env] = NULL;
			}
			free(mini_sh->data->env_sorted);
			mini_sh->data->env_sorted = NULL;
		}
	}
	printf("\n");
}

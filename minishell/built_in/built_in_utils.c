/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:52:55 by mael              #+#    #+#             */
/*   Updated: 2023/05/02 10:31:59 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	export_specific(char *to_export, t_mini_sh *mini_sh)
{
	int	i;

	mini_sh->data->new_envp = (char **)malloc(sizeof (char *) * \
		(mini_sh->data->size + 2));
	if (!mini_sh->data->new_envp)
		return (FAIL);
	mini_sh->data->new_envp[mini_sh->data->size + 1] = 0;
	i = -1;
	while (mini_sh->env[++i])
		mini_sh->data->new_envp[i] = ft_strdup(mini_sh->env[i]);
	mini_sh->data->new_envp[i] = ft_strdup(to_export);
	ft_free_tab(mini_sh->env);
	mini_sh->env = (char **)malloc(sizeof (char *) * (mini_sh->data->size + 2));
	if (!mini_sh->env)
		return (FAIL);
	i = -1;
	while (mini_sh->data->new_envp[++i])
		mini_sh->env[i] = ft_strdup(mini_sh->data->new_envp[i]);
	mini_sh->env[mini_sh->data->size + 1] = 0;
	ft_free_tab(mini_sh->data->new_envp);
	sort_export(mini_sh);
	return (SUCCESS);
}

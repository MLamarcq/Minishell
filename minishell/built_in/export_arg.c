/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:44:47 by mael              #+#    #+#             */
/*   Updated: 2023/04/14 16:06:15 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int g_exit_stt;

int	init_env_sorted(t_mini_sh *mini_sh)
{
	int	i;

	i = 0;
	mini_sh->data->env_sorted = (char **)malloc(sizeof(char *) * \
		(mini_sh->data->size + 1));
	if (!mini_sh->data->env_sorted)
		return (FAIL_MALLOC);
	mini_sh->data->env_sorted[mini_sh->data->size] = NULL;
	while (mini_sh->env[i])
	{
		mini_sh->data->env_sorted[i] = ft_strdup(mini_sh->env[i]);
		i++;
	}
	return (SUCCESS);
}

int	if_arg(char **argv, t_mini_sh *mini_sh)
{
	int	i;

	i = 0;
	if (ft_strncmp(argv[0], "export", 6) == 0)
	{
		mini_sh->data->dest = ft_strdup(argv[1]);
		while (mini_sh->data->dest[i])
		{
			if (mini_sh->data->dest[i] == '=')
				return (SUCCESS);
			i++;
		}
	}
	return (FAIL);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	realloc_tab(int *i, t_mini_sh *mini_sh)
{
	mini_sh->data->new_envp = (char **)malloc(sizeof (char *) * \
		(mini_sh->data->size + 2));
	if (!mini_sh->data->new_envp)
		return (FAIL_MALLOC);
	mini_sh->data->new_envp[mini_sh->data->size + 1] = 0;
	(*i) = -1;
	while (mini_sh->env[++(*i)])
		mini_sh->data->new_envp[(*i)] = ft_strdup(mini_sh->env[(*i)]);
	mini_sh->data->new_envp[(*i)] = ft_strdup(mini_sh->data->dest);
	ft_free_tab(mini_sh->env);
	mini_sh->env = (char **)malloc(sizeof (char *) * \
		(mini_sh->data->size + 2));
	if (!mini_sh->env)
		return (FAIL_MALLOC);
	(*i) = -1;
	while (mini_sh->data->new_envp[++(*i)])
		mini_sh->env[(*i)] = ft_strdup(mini_sh->data->new_envp[(*i)]);
	mini_sh->env[mini_sh->data->size + 1] = 0;
	ft_free_tab(mini_sh->data->new_envp);
	return (SUCCESS);
}

int	export_arg(char **argv, t_mini_sh *mini_sh)
{
	int	i;

	i = 0;
	if (if_arg(argv, mini_sh) == SUCCESS)
	{
		if (realloc_tab(&i, mini_sh) < 0)
			return (FAIL);
		export(argv, mini_sh);
		g_exit_stt = 0;
		return (SUCCESS);
	}
	g_exit_stt = 1;
	return (FAIL);
}

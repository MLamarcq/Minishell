/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:44:47 by mael              #+#    #+#             */
/*   Updated: 2023/04/28 14:57:07 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

int	alloc_new_tab(t_mini_sh *mini_sh)
{
	if (already_here(mini_sh) == SUCCESS)
	{
		mini_sh->data->new_envp = (char **)malloc(sizeof (char *) * \
			(mini_sh->data->size + 1));
		if (!mini_sh->data->new_envp)
			return (FAIL_MALLOC);
		mini_sh->data->new_envp[mini_sh->data->size] = 0;
	}
	else
	{
		mini_sh->data->new_envp = (char **)malloc(sizeof (char *) * \
		(mini_sh->data->size + 2));
		if (!mini_sh->data->new_envp)
			return (FAIL_MALLOC);
		mini_sh->data->new_envp[mini_sh->data->size + 1] = 0;
	}
	return (SUCCESS);
}

int	realloc_tab_util(t_mini_sh *mini_sh, int *check, int *i)
{
	if ((*check) == 0)
		mini_sh->data->new_envp[(*i)] = ft_strdup(mini_sh->data->dest);
	ft_free_tab(mini_sh->env);
	if ((*check) == 0)
	{
		mini_sh->env = (char **)malloc(sizeof (char *) * \
		(mini_sh->data->size + 2));
		if (!mini_sh->env)
			return (FAIL_MALLOC);
	}
	else
	{
		mini_sh->env = (char **)malloc(sizeof (char *) * \
		(mini_sh->data->size + 1));
		if (!mini_sh->env)
			return (FAIL_MALLOC);
	}
	(*i) = -1;
	while (mini_sh->data->new_envp[++(*i)])
		mini_sh->env[(*i)] = ft_strdup(mini_sh->data->new_envp[(*i)]);
	return (SUCCESS);
}

int	realloc_tab(int *i, t_mini_sh *mini_sh)
{
	int	check;

	check = 0;
	if (alloc_new_tab(mini_sh) < 0)
		return (FAIL);
	(*i) = -1;
	while (mini_sh->env[++(*i)])
	{
		mini_sh->data->new_envp[(*i)] = ft_strdup(mini_sh->env[(*i)]);
		if (are_they_the_same(mini_sh, *i) == SUCCESS)
		{
			free(mini_sh->data->new_envp[(*i)]);
			mini_sh->data->new_envp[(*i)] = ft_strdup(mini_sh->data->dest);
			check = 1;
		}
	}
	if (realloc_tab_util(mini_sh, &check, i) != SUCCESS)
		return (FAIL);
	if (check == 0)
		mini_sh->env[mini_sh->data->size + 1] = 0;
	else
		mini_sh->env[mini_sh->data->size] = 0;
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
		{
			g_exit_stt = 1;
			return (FAIL);
		}
		if (export(argv, mini_sh) == FAIL)
		{
			g_exit_stt = 1;
			return (FAIL);
		}
		g_exit_stt = 0;
		return (SUCCESS);
	}
	g_exit_stt = 1;
	return (FAIL);
}

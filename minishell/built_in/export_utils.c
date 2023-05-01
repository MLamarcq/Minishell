/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:35:49 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/05/01 15:35:50 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	init_env_sorted(t_mini_sh *mini_sh)
{
	int	i;

	i = 0;
	if (!mini_sh->env[i])
		return (FAIL);
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
		if (argv[1] && argv[1][0] == '-')
			printf("minishell: export: `%s' : option are not alllowed\n", \
			argv[1]);
		if (argv[1] && ft_isdigit(argv[1][0]) == 0)
		{
			mini_sh->data->dest = ft_strdup(argv[1]);
			while (mini_sh->data->dest[i])
			{
				if (mini_sh->data->dest[i] == '=')
					return (SUCCESS);
				i++;
			}
		}
		else
			printf("minishell: export: `%s' : not a valid identifier\n", \
				argv[1]);
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

int	are_they_the_same(t_mini_sh *mini_sh, int i)
{
	int		j;
	char	*buf;

	j = 0;
	while (mini_sh->data->new_envp[i][j])
	{
		if (mini_sh->data->new_envp[i][j] == '=')
			break ;
		j++;
	}
	buf = ft_strdup_len(mini_sh->data->new_envp[i], 0, j);
	if (ft_strncmp(buf, mini_sh->data->dest, ft_strlen(buf) - 1) == 0)
	{
		free(buf);
		return (SUCCESS);
	}
	free(buf);
	return (FAIL);
}

int	already_here(t_mini_sh *mini)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	while (mini->env[i])
	{
		j = 0;
		while (mini->env[i][j])
		{
			if (mini->env[i][j] == '=')
			{
				buf = ft_strdup_len(mini->env[i], 0, j);
				if (ft_strncmp(buf, mini->data->dest, ft_strlen(buf) - 1) == 0)
				{
					free(buf);
					return (SUCCESS);
				}
				free(buf);
			}
			j++;
		}
		i++;
	}
	return (FAIL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:32:26 by mael              #+#    #+#             */
/*   Updated: 2023/05/01 17:01:46 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

int	is_sorted(t_mini_sh *mini_sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!mini_sh->data->env_sorted)
		return (-2);
	while (mini_sh->data->env_sorted[i + 1])
	{
		j = 0;
		if (mini_sh->data->env_sorted[i][j] > \
			mini_sh->data->env_sorted[i + 1][j])
			return (FAIL);
		i++;
	}
	(void)j;
	return (SUCCESS);
}

void	swap_line(int i, t_mini_sh *mini_sh)
{
	mini_sh->data->temp = ft_strdup(mini_sh->data->env_sorted[i]);
	free(mini_sh->data->env_sorted[i]);
	mini_sh->data->env_sorted[i] = ft_strdup(mini_sh->data->env_sorted[i + 1]);
	free(mini_sh->data->env_sorted[i + 1]);
	mini_sh->data->env_sorted[i + 1] = ft_strdup(mini_sh->data->temp);
	free(mini_sh->data->temp);
}

void	sort_export(t_mini_sh *mini_sh)
{
	int	i;
	int	j;

	while (is_sorted(mini_sh) == FAIL)
	{
		i = 0;
		while (mini_sh->data->env_sorted[i + 1])
		{
			j = 0;
			if (mini_sh->data->env_sorted[i][j] > \
				mini_sh->data->env_sorted[i + 1][j])
				swap_line(i, mini_sh);
			else if (mini_sh->data->env_sorted[i][j] == \
				mini_sh->data->env_sorted[i + 1][j])
			{
				while (mini_sh->data->env_sorted[i][j] == \
					mini_sh->data->env_sorted[i + 1][j])
					j++;
				if (mini_sh->data->env_sorted[i][j] > \
					mini_sh->data->env_sorted[i + 1][j])
					swap_line(i, mini_sh);
			}
			i++;
		}
	}
}

int	export(char **argv, t_mini_sh *mini_sh)
{
	if (!mini_sh->data->env_sorted)
		return (FAIL);
	if (ft_strncmp(argv[0], "export", 6) == 0)
		sort_export(mini_sh);
	else
		return (FAIL);
	return (SUCCESS);
}

int	print_export(char **argv, t_mini_sh *mini_sh)
{
	int	i;

	i = 0;
	if (ft_strncmp(argv[0], "export", 6) == 0)
	{
		if (export(argv, mini_sh) == SUCCESS)
		{
			while (mini_sh->data->env_sorted[i])
			{
				printf("declare -x %s\n", mini_sh->data->env_sorted[i]);
				i++;
			}
			g_exit_stt = 0;
			return (SUCCESS);
		}
		else
			printf("Export failed\n");
		g_exit_stt = 1;
		return (FAIL);
	}
	else
		printf("\n");
	return (FAIL);
}

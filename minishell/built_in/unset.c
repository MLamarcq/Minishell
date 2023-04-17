/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:39:44 by mael              #+#    #+#             */
/*   Updated: 2023/04/17 12:31:58 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	to_empty_line(char **argv, t_mini_sh *mini_sh)
{
	int		i;
	int		len;
	char	*env_content;
	char	*dest;
	int		j;
	
	j = 0;
	i = 0;
	env_content = ft_find_var_env(mini_sh->env, argv[1]);
	while (mini_sh->env[i])
	{
		printf("%p: %s\n", mini_sh->env[i], mini_sh->env[i]);
		if (ft_strncmp(mini_sh->env[i], argv[1], ft_strlen(argv[1]) - 1) == 0)
		{
			len = ft_strlen(argv[1]) + 1;
			dest = malloc(sizeof(char) * ft_strlen(env_content) + 1);
			if (!dest)
				return ;
			while (mini_sh->env[i][len] && env_content[mini_sh->data->ite_genv] && mini_sh->env[i][len] == env_content[mini_sh->data->ite_genv])
			{
				mini_sh->data->ite_genv++;
				dest[j] = mini_sh->env[i][len];
				len++;
				mini_sh->data->count++;
				j++;
			}
			dest[j] = '\0';
			if (ft_strncmp(dest, env_content, ft_strlen(dest)) == 0)
			{
				ft_bzero(mini_sh->env[i], ft_strlen(mini_sh->env[i]));
				free(dest);
				if (env_content)
					free(env_content);
				env_content = NULL;
				break ;
			}
		}
		i++;
	}
	if (env_content)
		free(env_content);
	env_content = NULL;
}

int	check_unset_error(char **argv)
{
	if (ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) == 0)
	{
		printf("argv[1] = %s\n", argv[1]);
		int i;

		i = 0;
		while (argv[1][i])
		{
			if (argv[1][i] == '-')
			{
				if (i == 0)
				{
					printf("minishell: unset: no option allowed\n");
					return (FAIL);
				}
			}
			i++;
		}
	}
	return (SUCCESS);
}

int	unset(char **argv, t_mini_sh *mini_sh)
{
	if (check_unset_error(argv) == FAIL)
		return (FAIL);
	if (ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) == 0)
		to_empty_line(argv, mini_sh);
	return (SUCCESS);
}

int	exec_unset(char **argv, t_mini_sh *mini_sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (unset(argv, mini_sh) == FAIL)
		return (FAIL);
	while (mini_sh->env[i])
	{
		if (mini_sh->env[i][j] == '\0')
		{
			free(mini_sh->env[i]);
			while (mini_sh->env[i + 1])
			{
				mini_sh->env[i] = ft_strdup(mini_sh->env[i + 1]);
				free(mini_sh->env[i + 1]);
				i++;
			}
			mini_sh->env[i] = '\0';
		}
		i++;
	}
	return (SUCCESS);
}

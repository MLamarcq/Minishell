/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:44:47 by mael              #+#    #+#             */
/*   Updated: 2023/04/27 18:57:53 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

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
		// else if (argv[1] && ft_strncmp(argv[1], "-", 1) == 0)
		// 		printf("minishell: export: `%s' : option are not alllowed\n", 
		// 		argv[1]);
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
	int j;
	char *buf;
	j =0;
	//printf(PURPLE"mini_sh->data->new_envp[%d] = %s"RST"\n", i, mini_sh->data->new_envp[(i)]);
	while (mini_sh->data->new_envp[i][j])
	{
		if (mini_sh->data->new_envp[i][j] == '=')
			break ;
		j++;
	}
	buf = ft_strdup_len(mini_sh->data->new_envp[i], 0, j);
	// if (buf)
	// 	printf("buf = %s\n", buf);
	// printf(BOLD_BLUE"dest = %s"RST"\n", mini_sh->data->dest);
	// printf("j = %d\n", j);
	// printf("len_buf = %d\n", ft_strlen(buf));
	// printf("res = %d\n", ft_strncmp(buf, mini_sh->data->dest, ft_strlen(buf) - 1));
	if (ft_strncmp(buf, mini_sh->data->dest, ft_strlen(buf) - 1) == 0)
	{
		//printf(BOLD_GREEN"on y est"RST"\n");
		free(buf);
		return (SUCCESS);
	}
	//printf(BOLD_YELLOW"on y est pas"RST"\n");
	free(buf);
	return (FAIL);
}

int	already_here(t_mini_sh *mini_sh)
{
	int i;
	int j;
	char *buf;
	
	i = 0;
	while (mini_sh->env[i])
	{
		j = 0;
		while (mini_sh->env[i][j])
		{
			if (mini_sh->env[i][j] == '=')
			{
				buf = ft_strdup_len(mini_sh->env[i], 0, j);
				if (ft_strncmp(buf, mini_sh->data->dest, ft_strlen(buf) - 1) == 0)
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
	// buf = ft_strdup_len(mini_sh->data->env[i], 0, j);
	// if (ft_strncmp(buf, mini_sh->data->dest, ft_strlen(buf) - 1) == 0)
	// {
	// 	free(buf);
	// 	return (SUCCESS);
	// }
	// free(buf);
	return (FAIL);
}

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

int	realloc_tab(int *i, t_mini_sh *mini_sh)
{
	int check = 0;
	// mini_sh->data->new_envp = (char **)malloc(sizeof (char *) * 
	// 	(mini_sh->data->size + 2));
	// if (!mini_sh->data->new_envp)
	// 	return (FAIL_MALLOC);
	// mini_sh->data->new_envp[mini_sh->data->size + 1] = 0;
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
	if (check == 0)
		mini_sh->data->new_envp[(*i)] = ft_strdup(mini_sh->data->dest);
	ft_free_tab(mini_sh->env);
	if (check == 0)
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
	}
	return (FAIL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:19:59 by mael              #+#    #+#             */
/*   Updated: 2023/04/21 16:54:09 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int g_exit_stt;

int check_num(char **tab)
{
	int i;
	int j;

	i = 1;
	if (tab[i])
	{
		if (ft_strlen(tab[i]) > 20)
			return (FAIL);
		while (tab[i])
		{
			j = 0;
			while (tab[i][j])
			{
				if ((tab[i][j] != '-' && tab[i][j] != '+' && \
					ft_isdigit(tab[i][j]) == 0) || i > 1)
					return (FAIL);
				j++;
			}
			i++;
		}
	}
	return (SUCCESS);
}

int	exit_len(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	check_arg(t_mini_sh *mini_sh)
{
	write(2, "exit: too many argument\n", 24);
	g_exit_stt = 1;
	if (mini_sh->len_prepare_exec > 1)
	{
		close_all(mini_sh);
		free_all(mini_sh);
		exit (1);
	}
	return ;
}

void	ft_exit_1(char **tab, t_mini_sh *mini_sh)
{
	if (exit_len(tab) > 2 && check_num(tab) == FAIL)
	{
		check_arg(mini_sh);
		return ;
	}
	if (tab[1] && check_num(tab) == FAIL)
	{
		write(2, "exit : ", 7);
		ft_putstr_fd(tab[1], 2);
		write(2, ": numeric argument required\n", 28);
		close_all(mini_sh);
		free_all(mini_sh);
		exit(2);
	}
}


void	ft_exit(char **tab, t_mini_sh *mini_sh)
{
	ft_exit_1(tab, mini_sh);
	if (exit_len(tab) == 1)
	{
		write(2, "exit\n", 5);
		free_all(mini_sh);
		exit(0);
	}
	else if (tab[1] && check_num(tab) == SUCCESS)
	{
		g_exit_stt = ft_atoi(tab[1]);
		write(2, "exit\n", 5);
		if (ft_strlen(tab[1]) == 20)
		{
			close_all(mini_sh);
			free_all(mini_sh);
			exit (2);
		}
		close_all(mini_sh);
		free_all(mini_sh);
		if (g_exit_stt < 0)
			exit(256 + (g_exit_stt % 256));
		exit (g_exit_stt % 256);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:50:24 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/15 20:54:19 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	free_prep_exec(t_mini_sh *mini_sh)
{
	int		free_third;
	int		free_second;

	free_third = 0;
	while (mini_sh->prepare_exec[free_third])
	{
		free_second = 0;
		while (mini_sh->prepare_exec[free_third][free_second])
		{
			free(mini_sh->prepare_exec[free_third][free_second]);
			mini_sh->prepare_exec[free_third][free_second] = NULL;
			free_second++;
		}
		if (mini_sh->prepare_exec[free_third])
		{
			free(mini_sh->prepare_exec[free_third]);
			mini_sh->prepare_exec[free_third] = NULL;
		}
		mini_sh->prepare_exec[free_third] = NULL;
		free_third++;
	}
	free(mini_sh->prepare_exec);
	mini_sh->prepare_exec = NULL;
}

void	free_tab_fd(t_mini_sh *mini_sh)
{
	int	i_free_fd;

	i_free_fd = 0;
	if (mini_sh->exec && mini_sh->exec->tab_fd)
	{
		while (mini_sh->exec->tab_fd && mini_sh->exec->tab_fd[i_free_fd])
		{
			printf(BACK_GREEN"on free dans tab_fd"RST"\n");
			free(mini_sh->exec->tab_fd[i_free_fd]);
			mini_sh->exec->tab_fd = NULL;
			i_free_fd++;
		}
		free(mini_sh->exec->tab_fd);
		mini_sh->exec->tab_fd = NULL;
	}
}

void	free_exec(t_mini_sh *mini_sh)
{
	if (mini_sh->prepare_exec)
		free_prep_exec(mini_sh);
	free_tab_fd(mini_sh);
	free_all_redir(mini_sh);
	if (mini_sh->sep_type)
	{
		free(mini_sh->sep_type);
		mini_sh->sep_type = NULL;
	}
	if (mini_sh->exec)
	{
		free(mini_sh->exec);
		mini_sh->exec = NULL;
	}
	if (mini_sh->pids)
	{
		free(mini_sh->pids);
		mini_sh->pids = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:50:16 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/15 21:14:37 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	free_each_prpt(t_mini_sh *mini_sh)
{
	if (mini_sh->output && mini_sh->output[0] != 0)
		free_parsing(mini_sh);
	free_exec(mini_sh);
	//free_all_redir(mini_sh);
	printf(BACK_RED"on entre dans le free"RST"\n");
}

void	free_all_redir(t_mini_sh *mini_sh)
{
	if (mini_sh->sep_2)
	{
		if (mini_sh->exec->nbr_fd_app && mini_sh->exec->nbr_fd_app > 0)
			free_append(mini_sh);
		if (mini_sh->exec->nbr_fd_l && mini_sh->exec->nbr_fd_l > 0)
			free_redir_l(mini_sh);
		if (mini_sh->exec->nbr_fd_hr && mini_sh->exec->nbr_fd_hr > 0)
			free_hr_doc(mini_sh);
		if (mini_sh->exec->nbr_fd_r && mini_sh->exec->nbr_fd_r > 0)
			free_redir_r(mini_sh);
	}
}

void	free_all(t_mini_sh *mini_sh)
{
	free_each_prpt(mini_sh);
	free_env(mini_sh);
	free_env_sorted(mini_sh);
	free_data(mini_sh);
}

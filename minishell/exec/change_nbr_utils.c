/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_nbr_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:47:34 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/05/02 16:00:25 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	change_nbr_r_util(t_mini_sh *mini_sh, t_parse *temp, int *check)
{
	if (is_sep_int(temp->type) == SUCCESS)
	{
		if (temp->type == REDIR_R)
			(*check) = 1;
		if ((*check) == 1)
			mini_sh->exec->nbr_fd_r = mini_sh->exec->nbr_fd_r - 1;
		return (SUCCESS);
	}
	return (FAIL);
}

int	change_nbr_l_util(t_mini_sh *mini_sh, t_parse *temp, int *check)
{
	if (is_sep_int(temp->type) == SUCCESS)
	{
		if (temp->type == REDIR_L)
			(*check) = 1;
		if ((*check) == 1)
			mini_sh->exec->nbr_fd_l = mini_sh->exec->nbr_fd_l - 1;
		return (SUCCESS);
	}
	return (FAIL);
}

int	change_nbr_hr_util(t_mini_sh *mini_sh, t_parse *temp, int *check)
{
	if (is_sep_int(temp->type) == SUCCESS)
	{
		if (temp->type == HR_DOC)
			(*check) = 1;
		if ((*check) == 1)
			mini_sh->exec->nbr_fd_hr = mini_sh->exec->nbr_fd_hr - 1;
		return (SUCCESS);
	}
	return (FAIL);
}

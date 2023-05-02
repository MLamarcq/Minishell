/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 07:15:52 by gael              #+#    #+#             */
/*   Updated: 2023/05/02 08:16:33 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	change_nbr_l_util(t_mini_sh *mini_sh, t_parse *temp, int *check)
{
	if (is_sep(temp->word) == SUCCESS)
	{
		if (temp->type == RDR_L)
			(*check) = 1;
		if ((*check) == 1)
			mini_sh->exec->nbr_fd_l = mini_sh->exec->nbr_fd_l - 1;
		return (SUCCESS);
	}
	return (FAIL);
}

int	change_nbr_r_util(t_mini_sh *mini_sh, t_parse *temp, int *check)
{
	if (is_sep(temp->word) == SUCCESS)
	{
		if (temp->type == RDR_R)
			(*check) = 1;
		if ((*check) == 1)
			mini_sh->exec->nbr_fd_r = mini_sh->exec->nbr_fd_r - 1;
		return (SUCCESS);
	}
	return (FAIL);
}

int	change_nbr_hr_util(t_mini_sh *mini_sh, t_parse *temp, int *check)
{
	if (is_sep(temp->word) == SUCCESS)
	{
		if (temp->type == HR_DOC)
			(*check) = 1;
		if ((*check) == 1)
			mini_sh->exec->nbr_fd_hr = mini_sh->exec->nbr_fd_hr - 1;
		return (SUCCESS);
	}
	return (FAIL);
}

int	change_nbr_append_util(t_mini_sh *mini_sh, t_parse *temp, int *check)
{
	if (is_sep(temp->word) == SUCCESS)
	{
		if (temp->type == APPEND)
			(*check) = 1;
		if ((*check) == 1)
			mini_sh->exec->nbr_fd_app = mini_sh->exec->nbr_fd_app - 1;
		return (SUCCESS);
	}
	return (FAIL);
}

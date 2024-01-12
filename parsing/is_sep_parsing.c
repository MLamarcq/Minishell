/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sep_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:02:35 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/04/28 15:52:30 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	issep_read(int type)
{
	if (type == REDIR_L)
		return (SUCCESS);
	if (type == HR_DOC)
		return (SUCCESS);
	return (FAIL);
}

int	issep_write(int type)
{
	if (type == REDIR_R)
		return (SUCCESS);
	if (type == APPEND)
		return (SUCCESS);
	return (FAIL);
}

int	is_all(int type)
{
	if (type == REDIR_R)
		return (SUCCESS);
	if (type == APPEND)
		return (SUCCESS);
	if (type == REDIR_L)
		return (SUCCESS);
	if (type == HR_DOC)
		return (SUCCESS);
	return (FAIL);
}

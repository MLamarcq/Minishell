/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:45:52 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/23 19:48:00 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	toggle_ti_pipe(t_mini_sh *mini_sh)
{
	if (mini_sh->thereis_pipe == FAIL)
		mini_sh->thereis_pipe = SUCCESS;
	else
		mini_sh->thereis_pipe = FAIL;
}

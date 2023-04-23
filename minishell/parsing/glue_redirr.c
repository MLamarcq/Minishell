/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glue_redirr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:39:11 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/04/21 18:24:28 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	detect_redirr_glue(t_mini_sh *mini_sh, int *is_did, int *glue, int ite)
{
	*is_did = FAIL;
	if (mini_sh->output[ite] == '>' && ft_is_sep_parse(mini_sh->output[ite - 1])
	== FAIL && (mini_sh->output[ite - 1] != '>' && mini_sh->output[ite + 1] != '>'))
	{
		*glue = ite;
		*is_did = SUCCESS;
	}
	else if (mini_sh->output[ite] == '>' && ft_is_sep_parse(mini_sh->output[ite + 1])
	== FAIL && (mini_sh->output[ite - 1] != '>' && mini_sh->output[ite + 1] != '>'))
	{
		*glue = ite + 1;
		*is_did = SUCCESS;
	}
}

void	set_after_glue_redirr(t_mini_sh *mini_sh, int glue)
{
	char	*tmp;
	char	*line;

	tmp = ft_strdup_len(mini_sh->output, 0, glue);
	tmp = ft_strjoin_lfree(tmp, " ");
	line = mini_sh->output;
	mini_sh->output = ft_strjoin_dfree(tmp, \
	ft_strdup_len(mini_sh->output, \
	ft_strlen(tmp) - 1, ft_strlen(mini_sh->output)));
	free(line);
}

void	glue_redirr(t_mini_sh *mini_sh)
{
	int		ite;
	int		glue;
	int		is_did;

	is_did = FAIL;
	glue = 0;
	ite = 0;
	while (mini_sh->output[ite])
	{
		while (ft_is_sep_parse(mini_sh->output[ite]) == SUCCESS)
			ite++;
		while (mini_sh->output[ite] \
		&& ft_is_sep_parse(mini_sh->output[ite]) == FAIL)
		{
			count_quote_arg(mini_sh->output, &ite);
			if (ite != 0)
				detect_redirr_glue(mini_sh, &is_did, &glue, ite);
			if (is_did == SUCCESS)
			{
				set_after_glue_redirr(mini_sh, glue);
				ite = 0;
			}
			ite++;
		}
	}
}

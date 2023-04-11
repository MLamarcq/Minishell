/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glue.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:32:17 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/11 17:22:22 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	detect_space_glue(t_mini_sh *mini_sh, int *is_did, int *glue, int ite)
{
	*is_did = FAIL;
	if (mini_sh->output[ite] == '|' \
	&& ft_is_sep_parse(mini_sh->output[ite - 1]) == FAIL)
	{
		*glue = ite;
		*is_did = SUCCESS;
	}
	else if (mini_sh->output[ite] == '|' \
	&& ft_is_sep_parse(mini_sh->output[ite + 1]) == FAIL)
	{
		*glue = ite + 1;
		*is_did = SUCCESS;
	}
}

void	set_after_glue(t_mini_sh *mini_sh, int glue)
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

void	is_glue(t_mini_sh *mini_sh)
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
			detect_space_glue(mini_sh, &is_did, &glue, ite);
			if (is_did == SUCCESS)
			{
				set_after_glue(mini_sh, glue);
				ite = 0;
			}
			ite++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glue_hrdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:32:17 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/13 15:43:32 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	detect_hrdoc_glue(t_mini_sh *mini_sh, int *is_did, int *glue, int ite)
{
	*is_did = FAIL;
	if ((mini_sh->output[ite] == '<' && mini_sh->output[ite + 1] == '<')
	&& ft_is_sep_parse(mini_sh->output[ite - 1]) == FAIL)
	{
		*glue = ite;
		*is_did = SUCCESS;
	}
	else if ((mini_sh->output[ite] == '<' && mini_sh->output[ite + 1] == '<')
	&& ft_is_sep_parse(mini_sh->output[ite + 2]) == FAIL)
	{
		*glue = ite + 2;
		*is_did = SUCCESS;
	}
}

void	set_after_glue_hrdoc(t_mini_sh *mini_sh, int glue)
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

void	glue_hrdoc(t_mini_sh *mini_sh)
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
			detect_hrdoc_glue(mini_sh, &is_did, &glue, ite);
			// else if (mini_sh->output[ite] == '<' && mini_sh->output[ite + 1] == '<')
			// 	detect_hrdoc_glue(mini_sh, &is_did, &glue, ite);
			if (is_did == SUCCESS)
			{
				printf(BACK_GREEN"mini_sh->output: %s"RST"\n", mini_sh->output);
				set_after_glue_hrdoc(mini_sh, glue);
				printf(BACK_GREEN"mini_sh->output: %s"RST"\n", mini_sh->output);
				ite = 0;
			}
			ite++;
		}
	}
}

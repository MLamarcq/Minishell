/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glue.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:32:17 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/10 16:45:16 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	is_glue(t_mini_sh *mini_sh)
{
	int		ite;
	int		glue;
	int		is_did;
	char	*tmp;
	char	*line;

	is_did = FAIL;
	glue = 0;
	ite = 0;
	while (mini_sh->output[ite])
	{
		while (ft_is_sep_parse(mini_sh->output[ite]) == SUCCESS)
			ite++;
		while (mini_sh->output[ite] && ft_is_sep_parse(mini_sh->output[ite]) == FAIL)
		{
			is_did = FAIL;
			count_quote_arg(mini_sh->output, &ite);
			if (mini_sh->output[ite] == '|' && ft_is_sep_parse(mini_sh->output[ite - 1]) == FAIL)
			{
				printf(RED"letter left"RESET"\n");
				glue = ite;
				is_did = SUCCESS;
			}
			else if (mini_sh->output[ite] == '|' && ft_is_sep_parse(mini_sh->output[ite + 1]) == FAIL)
			{
				printf(RED"letter right"RESET"\n");
				glue = ite + 1;
				is_did = SUCCESS;
			}
			if (is_did == SUCCESS)
			{
				tmp = ft_strdup_len(mini_sh->output, 0, glue);
				tmp = ft_strjoin_lfree(tmp, " ");
				printf("------------------------------\n");
				printf(PURPLE"ft_strlen(mini_sh->output): %i"RESET"\n", ft_strlen(mini_sh->output));
				printf("------------------------------\n");
				line = mini_sh->output;
				mini_sh->output = ft_strjoin_dfree(tmp, ft_strdup_len(mini_sh->output, ft_strlen(tmp) - 1, ft_strlen(mini_sh->output)));
				free(line);
				printf(BACK_GREEN"%s"RST"\n", mini_sh->output);
				// mini_sh->ou`tput = tmp;
				ite = 0;
			}
			ite++;
		}
	}
	(void)tmp;
	(void)line;
	(void)glue;
	// return (line);
}

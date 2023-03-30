/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:10:55 by gael              #+#    #+#             */
/*   Updated: 2023/03/30 12:16:56 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	is_built_in(t_mini_sh *mini_sh)
{
	if (ft_strncmp(mini_sh->rl_out->word, "pwd", \
		ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(mini_sh->rl_out->word, "cd", \
		ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(mini_sh->rl_out->word, "echo", \
		ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(mini_sh->rl_out->word, "unset", \
		ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(mini_sh->rl_out->word, "env", \
		ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(mini_sh->rl_out->word, "export", \
		ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(mini_sh->rl_out->word, "echo", \
		ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(mini_sh->rl_out->word, "exit", \
		ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	return (FAIL);
}

void	put_word_in_minish(t_mini_sh *mn_sh, char *lne, int *save, int *ite)
{
	t_parse	*new;

	new = ft_lstnew_word(lne, (*save), (*ite));
	if ((*ite) - (*save) > 0)
	{
		if (mn_sh->rl_out == NULL)
		{
			mn_sh->rl_out = new;
			mn_sh->rl_out_head = mn_sh->rl_out;
		}
		else
			ft_lstadd_back((&mn_sh->rl_out), new);
	}
}

int	build_result_output(t_mini_sh *mini_sh, char *line)
{
	int	ite;
	int	save;

	mini_sh->rl_out = NULL;
	save = 0;
	ite = 0;
	while (line[ite])
	{
		while (ft_is_sep_parse(line[ite]) == SUCCESS)
			ite++;
		save = ite;
		while (line[ite] != '\0' && ft_is_sep_parse(line[ite]) == FAIL)
		{
			count_quote_arg(line, &ite, D_QUOTE);
			count_quote_arg(line, &ite, S_QUOTE);
			ite++;
		}
		put_word_in_minish(mini_sh, line, &save, &ite);
	}
	return (SUCCESS);
}

int	ft_parsing(t_mini_sh *mini_sh)
{
	mini_sh->is_dquote = FAIL;
	mini_sh->is_squote = FAIL;
	if (check_quote_is_closed(mini_sh->output) > 0)
	{
		if (build_result_output(mini_sh, mini_sh->output) < 0)
			return (FAIL);
		expand(mini_sh);
		if (set_type(mini_sh) == FAIL)
			return (FAIL);
		remove_quote_2(mini_sh);
		if (check_redi_r_error(mini_sh) == FAIL)
			return (FAIL);
		if (prepare_exec(mini_sh) < 0)
			return (FAIL);
	}
	else
		return (FAIL);
	return (SUCCESS);
}

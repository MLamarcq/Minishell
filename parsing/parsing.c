/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:10:55 by gael              #+#    #+#             */
/*   Updated: 2023/05/02 15:59:31 by mlamarcq         ###   ########.fr       */
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

void	put_word_in_minish(t_mini_sh *mini, char *lne, int *sv, int *ite)
{
	if ((*ite) - (*sv) > 0)
	{
		if (mini->rl_out == NULL)
		{
			mini->rl_out = ft_lstnew_word(lne, (*sv), (*ite));
			mini->rl_out_head = mini->rl_out;
		}
		else
			ft_lstadd_back((&mini->rl_out), ft_lstnew_word(lne, (*sv), (*ite)));
	}
}

int	build_result_output(t_mini_sh *mini_sh, char *line)
{
	int	ite;
	int	save;

	mini_sh->rl_out = NULL;
	save = 0;
	ite = 0;
	if (!mini_sh->output[0])
		return (FAIL);
	while (line[ite])
	{
		while (ft_is_sep_parse(line[ite]) == SUCCESS)
			ite++;
		save = ite;
		while (line[ite] != '\0' && ft_is_sep_parse(line[ite]) == FAIL)
		{
			count_quote_arg(line, &ite);
			ite++;
		}
		put_word_in_minish(mini_sh, line, &save, &ite);
	}
	return (SUCCESS);
}

int	check_rdr_follow(t_mini_sh *mini_sh)
{
	int	err;

	err = FAIL;
	mini_sh->rl_out = mini_sh->rl_out_head;
	while (mini_sh->rl_out)
	{
		if (is_sep_int(mini_sh->rl_out->type) == SUCCESS \
		&& mini_sh->rl_out->next \
		&& is_sep_int(mini_sh->rl_out->next->type) == SUCCESS)
			err = SUCCESS;
		if (is_sep_int(mini_sh->rl_out->type) == SUCCESS && \
		(mini_sh->rl_out->next && (ft_strncmp(">", \
		mini_sh->rl_out->next->word, 0) == 0 || ft_strncmp("<", \
		mini_sh->rl_out->next->word, 0) == 0 || ft_strncmp(">>", \
		mini_sh->rl_out->next->word, 1) == 0 || ft_strncmp("<<", \
		mini_sh->rl_out->next->word, 1) == 0)))
			err = SUCCESS;
		if (mini_sh->rl_out->type == PIPE && mini_sh->rl_out->next \
		&& issep_read(mini_sh->rl_out->next->type) == SUCCESS)
			err = FAIL;
		if (err == SUCCESS)
			return (print_error(4, mini_sh->rl_out), SUCCESS);
		mini_sh->rl_out = mini_sh->rl_out->next;
	}
	return (FAIL);
}

int	ft_parsing(t_mini_sh *mini_sh)
{
	mini_sh->is_dquote = FAIL;
	mini_sh->is_squote = FAIL;
	if (check_quote_is_closed(mini_sh->output) > 0)
	{
		all_glue(mini_sh);
		if (build_result_output(mini_sh, mini_sh->output) < 0)
			return (FAIL);
		expand(mini_sh);
		if (set_type(mini_sh) == FAIL)
			return (FAIL);
		if (check_rdr_follow(mini_sh) == SUCCESS)
			return (FAIL);
		remove_quote_2(mini_sh);
		set_index(mini_sh);
		all_move(mini_sh);
		if (check_redi_r_append_error(mini_sh) == FAIL)
			return (FAIL);
		if (prepare_exec(mini_sh) < 0)
			return (FAIL);
	}
	else
		return (FAIL);
	return (SUCCESS);
}

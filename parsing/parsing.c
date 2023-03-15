/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:10:55 by gael              #+#    #+#             */
/*   Updated: 2023/03/14 17:24:07 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	print_word(char *new_w)
{
	int	x;

	x = 0;
	while (new_w[x])
	{
		printf(BACK_CYAN"%c"RST"", new_w[x]);
		x++;
	}
	printf(BACK_RED"%i"RST"\n", new_w[x]);
}

void	print_word2(char *new_w)
{
	int x = 0;
	while (new_w[x])
	{
		printf(BACK_PURPLE"%c"RST"", new_w[x]);
		x++;
	}
	printf(BACK_YELLOW"%i"RST"\n", new_w[x]);
}

void	ft_print_rl_out(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	printf("\n");
	printf(" ----- ----- ----- ----- ----- \n\n");
	while (tmp)
	{
		print_word(tmp->word);
		if (tmp->type)
		{
			if (tmp->type == CMD)
				printf(BLUE"CMD"RST"\n");
			if (tmp->type == CMD_ABS)
				printf(BLUE"CMD_ABS"RST"\n");
			if (tmp->type == PIPE)
				printf(BLUE"PIPE"RST"\n");
			if (tmp->type == ARG)
				printf(BLUE"ARG"RST"\n");
			if (tmp->type == REDIR_L)
				printf(BLUE"REDIR_L"RST"\n");
			if (tmp->type == APPEND)
				printf(BLUE"APPEND"RST"\n");
			if (tmp->type == HR_DOC)
				printf(BLUE"HR_DOC"RST"\n");
			if (tmp->type == REDIR_R)
				printf(BLUE"REDIR_R"RST"\n");
			if (tmp->type == OPTION)
				printf(BLUE"OPTION"RST"\n");
			if (tmp->type == _FILE)
				printf(BLUE"_FILE"RST"\n");
			if (tmp->type == BUILT_IN)
				printf(BLUE"BUILT_IN"RST"\n");
			printf("\n");
		}
		tmp = tmp->next;
	}
}

void	put_word_in_minish(t_mini_sh *mini_sh, char *line, int *save, int *ite)
{
	t_parse	*new;

	new = ft_lstnew_word(line, (*save), (*ite));
	if ((*ite) - (*save) > 0)
	{
		if (mini_sh->rl_out == NULL)
		{
			mini_sh->rl_out = new;
			mini_sh->rl_out_head = mini_sh->rl_out;
		}
		else
			ft_lstadd_back((&mini_sh->rl_out), new);
	}
}

int	build_result_output(t_mini_sh *mini_sh, char *line)
{
	int				len_global;
	int				ite;
	int				save;

	mini_sh->rl_out = NULL;
	save = 0;
	ite = 0;
	len_global = check_quote_is_closed(line);
	if (len_global > 0)
	{
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
		ft_print_rl_out(mini_sh);
		expand(mini_sh);
		if (set_type(mini_sh) == FAIL)
			return (printf(" ----- something wrong happend ----- \n"), FAIL);
		ft_print_rl_out(mini_sh);
		if (prepare_exec(mini_sh) < 0)
			return (FAIL);
	}
	else
		return (FAIL);
	return (SUCCESS);
}

int	ft_parsing(t_mini_sh *mini_sh)
{
	mini_sh->is_dquote = FAIL;
	mini_sh->is_squote = FAIL;
	if (build_result_output(mini_sh, mini_sh->output) < 0)
		return (FAIL); 
	return (SUCCESS);
	(void)mini_sh;
}

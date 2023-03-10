/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:10:55 by gael              #+#    #+#             */
/*   Updated: 2023/03/10 10:53:43 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	print_word(char *new_w)
{
	int x = 0;
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
	t_arr_output	*tmp;

	tmp = mini_sh->rl_out_head;
	printf("\n");
	printf(" ----- ----- ----- ----- ----- \n\n");
	while (tmp)
	{
		print_word(tmp->word);
		// if (tmp->word)
		// 	printf(RED"tmp->word: %s\n"RST, tmp->word);
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
		}
		printf("\n");
		tmp = tmp->next;
	}
}

void	put_word_in_minish(t_mini_sh *mini_sh, char *line, int *save, int *ite)
{
	t_arr_output	*new;

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
			// printf("mini_sh->rl_out->word: %s\n", mini_sh->rl_out->word);
		}
		ft_print_rl_out(mini_sh);
		expand(mini_sh);
		if (set_type(mini_sh) == FAIL)
			return (printf(" ----- something wrong happend ----- \n"), FAIL);
		// remove_quote(mini_sh); 
		ft_print_rl_out(mini_sh);
		if (prepare_exec(mini_sh) < 0)
			return (FAIL);
	}
	return (len_global + 1);
}

int	ft_parsing(t_mini_sh *mini_sh)
{
	mini_sh->is_dquote = FAIL;
	mini_sh->is_squote = FAIL;
	// test count_word
	// printf("$				 %i 0\n------------------------------------------------\n", build_result_output(mini_sh, ""));
	// printf("\"$				%i -1\n------------------------------------------------\n", build_result_output(mini_sh, "\""));
	// printf("\"\"$				 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "\"\""));
	// printf("\"e\"$				 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "\"e\""));
	// printf("\"abcdef\"$			 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "\"abcdef\""));
	// printf("cat |$				 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "cat |"));
	// printf("|$				 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "|"));
	// printf("< /usr/bin/ls -la -le | cat > out$				 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "< /usr/bin/ls -la -le | cat > out"));
	// printf("ls$				 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "ls"));
	// printf("  \"abcdef\"  $			 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "  \"abcdef\"  "));
	// printf("  abcdef  $			 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "  abcdef  "));
	// printf("  abc\"def\"ghi  $		 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "  abc\"def\"ghi  "));
	// printf("  abc\"def\"ghi  $		 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "  abc\"def\"ghi  "));
	// printf("  \"abc def\"  $			 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "  \"abc def\"  "));
	// printf("  abc def  $			 %i 2\n------------------------------------------------\n", build_result_output(mini_sh, "  abc def  "));
	// printf("  0123 \"abc def\"  $		 %i 2\n------------------------------------------------\n", build_result_output(mini_sh, "  0123 \"abc def\"  "));
	// printf("  0123 | \"abc def\"  $		 %i 3\n------------------------------------------------\n", build_result_output(mini_sh, "  0123 | \"abc def\"  "));
	// printf("  0123 \"abc'def\" xyz'  $	%i -1\n------------------------------------------------\n", build_result_output(mini_sh, "  0123 \"abc'def\" xyz'  "));
	// printf("  < 	 lib  /usr/bin/grep -i | \"abc $TERM def\" \"\" | \'\"$TERM\"\' \"\'$TERM\'\" --color=never  	  >   \'$USER\'\" $abc\'$USER\'-$USER.txt\"   	| ls -l --color=never  	 -a | echo >\"|\" \"| >>\""BACK_RED"$	%i 22"RST"\n------------------------------------------------\n",
	// build_result_output(mini_sh, "  < 	 lib  /usr/bin/grep -i | \"abc $TERM def\" \"\" | \'\"$TERM\"\' \"\'$TERM\'\" --color=never 	  >   \'$USER\'\" $abc\'$USER\'-$USER.txt\"   	| ls -l --color=never 	 -a | echo \"|\" \"| >>\""));
	// printf("  < 	 lib  /usr/bin/grep -ri in | echo \"abc $TERM def\" $USER xyz \"$$\" \"$\" $ | echo \'\"$TERM\"\' \"\'$TERM\'\"   	  >   \'$USER\'\" $abc\'$USER\'-$USER.txt\"   	| ls -l  --color=never  	 -a | echo >\"|\" \"| >>\""BACK_RED"$	%i 27"RST"\n------------------------------------------------\n",
	// build_result_output(mini_sh, "  < 	 lib  /usr/bin/grep -ri in | echo \"abc $TERM def\" $USER xyz \"$$\" \"$\" $ | echo \'\"$TERM\"\' \"\'$TERM\'\"  	  >   \'$USER\'\" $abc\'$USER\'-$USER.txt\"   	| ls -l  --color=never 	 -a | echo \"|\" \"| >>\""));
	build_result_output(mini_sh, mini_sh->output);
	return (SUCCESS);
	(void)mini_sh;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:10:55 by gael              #+#    #+#             */
/*   Updated: 2023/03/02 12:03:11 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	ft_print_rl_out(t_mini_sh *mini_sh)
{
	t_arr_output	*tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		print_word(tmp->word);
		// if (tmp->word)
		// 	printf(RED"tmp->word: %s\n"RST, tmp->word);
		if (tmp->type)
		{
			if (tmp->type == CMD)
				printf(BLUE"CMD"RST"\n");
			if (tmp->type == PIPE)
				printf(BLUE"PIPE"RST"\n");
			if (tmp->type == ARG)
				printf(BLUE"ARG"RST"\n");
			if (tmp->type == REDIR_L)
				printf(BLUE"REDIR_L"RST"\n");
			if (tmp->type == REDIR_R)
				printf(BLUE"REDIR_R"RST"\n");
			if (tmp->type == OPTION)
				printf(BLUE"OPTION"RST"\n");
			if (tmp->type == _FILE)
				printf(BLUE"_FILE"RST"\n");
			if (tmp->type == HR_DOC)
				printf(BLUE"HR_DOC"RST"\n");
			if (tmp->type == APPEND)
				printf(BLUE"APPEND"RST"\n");
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
			while (ft_is_sep(line[ite]) == SUCCESS)
				ite++;
			save = ite;
			while (line[ite] != '\0' && ft_is_sep(line[ite]) == FAIL)
			{
				count_quote_arg(line, &ite, D_QUOTE);
				count_quote_arg(line, &ite, S_QUOTE);
				ite++;
			}
			put_word_in_minish(mini_sh, line, &save, &ite);
			// printf("mini_sh->rl_out->word: %s\n", mini_sh->rl_out->word);
		}
		expand(mini_sh);
		if (set_type(mini_sh) == FAIL)
			return (FAIL);
		ft_print_rl_out(mini_sh);
		// remove_quote(mini_sh);
		prepare_exec(mini_sh);
	}
	return (len_global);
}

int	ft_find_args(t_mini_sh *mini_sh, char *imput)
{
	// test count_word
	// printf("$				 %i 0\n------------------------------------------------\n", build_result_output(mini_sh, ""));
	// printf("\"$				%i -1\n------------------------------------------------\n", build_result_output(mini_sh, "\""));
	// printf("\"\"$				 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "\"\""));
	// printf("\"e\"$				 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "\"e\""));
	// printf("\"abcdef\"$			 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "\"abcdef\""));
	// printf("abcdef$				 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "abcdef"));
	// printf("  \"abcdef\"  $			 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "  \"abcdef\"  "));
	// printf("  abcdef  $			 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "  abcdef  "));
	// printf("  abc\"def\"ghi  $		 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "  abc\"def\"ghi  "));
	// printf("  abc\"def\"ghi  $		 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "  abc\"def\"ghi  "));
	// printf("  \"abc def\"  $			 %i 1\n------------------------------------------------\n", build_result_output(mini_sh, "  \"abc def\"  "));
	// printf("  abc def  $			 %i 2\n------------------------------------------------\n", build_result_output(mini_sh, "  abc def  "));
	// printf("  0123 \"abc def\"  $		 %i 2\n------------------------------------------------\n", build_result_output(mini_sh, "  0123 \"abc def\"  "));
	// printf("  0123 | \"abc def\"  $		 %i 3\n------------------------------------------------\n", build_result_output(mini_sh, "  0123 | \"abc def\"  "));
	// printf("  0123 \"abc'def\" xyz'  $	%i -1\n------------------------------------------------\n", build_result_output(mini_sh, "  0123 \"abc'def\" xyz'  "));
	//printf("  < 	 main.c  /usr/bin/grep -i \'\"$USER\"\' \"\'$USER\'\" --color=never  	  >   \'$USER\'\" \'$USER\'-$USER.txt\"   	| ls -l --color=never  	 -a | echo \"|\" \"| >>\""BACK_RED"$	%i 19"RST"\n------------------------------------------------\n",
	if(build_result_output(mini_sh, imput) == FAIL)
		return (FAIL);
	t_arr_output	*tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		printf("-> %s\n", tmp->word);
		tmp = tmp->next;
	}
	return (SUCCESS);
	(void)mini_sh;
}

/*

int	count_word(char *line)
{
	int	ite;
	int	len;

	len = 0;
	ite = 0;
	while (line[ite])
	{
		while (ft_is_sep(line[ite]) == SUCCESS)
			ite++;
		if (line[ite] != '\0' && ft_is_sep(line[ite]) == FAIL)
			len++;
		while (line[ite] != '\0' && ft_is_sep(line[ite]) == FAIL)
		{
			printf("%c", line[ite]);
			ite++;
		}
	}
	return (len);
}
int main(void)
{
	char	*input;

	count_word("ls -l --color=never 	 -a | /usr/bin/grep -i --color=never  	   in >     result.txt");
	input = readline(">");
	printf("input: %s\n"RESET, input);
	return (0);
}
*/

/*

int	build_result_output(t_mini_sh *mini_sh, char *line)
{
	t_arr_output	rl_out;
	int	len_global;
	int	len_word;
	int	ite;

	mini_sh->rl_out = (&rl_out);
	ite = 0;
	len_word = 0;
	len_global = check_quote_is_closed(line);
	if (len_global > 0)
	{
		while (line[ite])
		{
			while (ft_is_sep(line[ite]) == SUCCESS)
				ite++;
			// if (line[ite] != '\0' && ft_is_sep(line[ite]) == FAIL)
			// 	len_list++;
			len_word = 0;
			while (line[ite] != '\0' && ft_is_sep(line[ite]) == FAIL)
			{
				len_word++;
				ite++;
			}
			if (len_word > 0)
				rl_out.word = malloc(sizeof (char) * (len_word + 1));
		}
		ite = 0;
		while (line[ite])
		{
			while (ft_is_sep(line[ite]) == SUCCESS)
				ite++;
			// if (line[ite] != '\0' && ft_is_sep(line[ite]) == FAIL)
			// 	len_list++;
			len_word = 0;
			while (line[ite] != '\0' && ft_is_sep(line[ite]) == FAIL)
			{
				rl_out.word[len_word] = line[ite];
				len_word++;
				ite++;
			}
			if (len_word > 0)
			{
				printf(GREEN"rl_out.word: %s"RST"\n", rl_out.word);
				rl_out.word[len_word] = '\0';
			}
		}
		printf(BACK_GREEN"mini_sh->rl_out->word: %s"RST"\n", mini_sh->rl_out->word);
	}
	return (len_global);
	(void)line;
	(void)len_global;
	(void)rl_out;
	(void)mini_sh;
}

*/
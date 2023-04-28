/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:46:59 by gael              #+#    #+#             */
/*   Updated: 2023/04/27 19:29:20 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	print_word(char *new_w)
{
	int	x;

	x = 0;
	while (new_w[x])
	{
		// printf(BACK_CYAN"%c"RST"", new_w[x]);
		x++;
	}
	// printf(BACK_RED"%i"RST"\n", new_w[x]);
}

void	print_word2(char *new_w)
{
	int	x;

	x = 0;
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
	int	i;
	
	i = 0;
	tmp = mini_sh->rl_out_head;
	// printf("\n...............start..................\n\n");
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		print_word(tmp->word);
		if (tmp->type)
			print_type(tmp->type);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
		if (i > 10)
			break ;
		i++;
	}
	// printf("\n.............reverse...................\n\n");
	while (tmp->prev)
	{
		print_word(tmp->word);
		if (tmp->type)
			print_type(tmp->type);
		tmp = tmp->prev;
		if (i > 10)
			break ;
		i++;
	}
	print_word(tmp->word);
	if (tmp->type)
		print_type(tmp->type);
	// printf("\n............end................\n\n");
}

void	print_type(int type)
{
	if (type == CMD)
		fprintf(stderr, BLUE"CMD"RST"\n");
	else if (type == CMD_ABS)
		fprintf(stderr, BLUE"CMD_ABS"RST"\n");
	else if (type == PIPE)
		fprintf(stderr, BLUE"PIPE"RST"\n");
	else if (type == ARG)
		fprintf(stderr, BLUE"ARG"RST"\n");
	else if (type == REDIR_L)
		fprintf(stderr, BLUE"REDIR_L"RST"\n");
	else if (type == APPEND)
		fprintf(stderr, BLUE"APPEND"RST"\n");
	else if (type == HR_DOC)
		fprintf(stderr, BLUE"HR_DOC"RST"\n");
	else if (type == REDIR_R)
		fprintf(stderr, BLUE"REDIR_R"RST"\n");
	else if (type == OPTION)
		fprintf(stderr, BLUE"OPTION"RST"\n");
	else if (type == _FILE)
		fprintf(stderr, BLUE"_FILE"RST"\n");
	else if (type == BUILT_IN)
		fprintf(stderr, BLUE"BUILT_IN"RST"\n");
	else if (type == EOFL)
		fprintf(stderr, BLUE"EOFL"RST"\n");
	else
		fprintf(stderr, BACK_RED"0"RST"\n");
	fprintf(stderr, "\n");
}

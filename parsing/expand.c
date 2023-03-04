/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 02:21:41 by gael              #+#    #+#             */
/*   Updated: 2023/02/27 14:22:26 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_isthere_dollar(char *str, t_mini_sh *min)
{
	int	ite_isdollar;
	int	is_squote;

	is_squote = FAIL;
	ite_isdollar = -1;
	while (str[++ite_isdollar])
	{
		check_qt_open(str, min, &ite_isdollar, &is_squote);
		if (is_squote == SUCCESS)
		{
			if (str[ite_isdollar] == '$')
				return (SUCCESS);
		}
	}
	(void)is_squote;
	return (FAIL);
}

void	check_qt_open(char *line, t_mini_sh *min, int *i_expnd, int *is_qt)
{
	(void)is_qt;
	if (line[*i_expnd] == S_QUOTE)
	{
		min->is_squote = SUCCESS;
		min->is_dquote = FAIL;
	}
	else if (line[*i_expnd] == D_QUOTE)
	{
		min->is_dquote = SUCCESS;
		min->is_squote = FAIL;
	}
	// if (line[*i_expnd] == D_QUOTE)
	// {
	// 	if ((*is_qt) == FAIL)
	// 		(*is_qt) = SUCCESS;
	// 	else
	// 		(*is_qt) = FAIL;
	// }
}

void	ft_replace_dollar(t_mini_sh *mn_sh, t_arr_output *mn_tmp, int *i_expnd)
{
	char	*new_w;
	int		save;
	char	*dup_len1;
	char	*dup_len2;
	char	*dup_len3;

	save = 0;
	new_w = NULL;
	save = (*i_expnd);
	(*i_expnd)++;
	while (ft_is_valid_export(mn_tmp->word[(*i_expnd)]) == SUCCESS)
		(*i_expnd)++;
	new_w = ft_strdup_len(mn_tmp->word, 0, save);
	dup_len2 = ft_strdup_len(mn_tmp->word, save + 1, (*i_expnd));
	dup_len3 = ft_find_var_env(mn_sh->env, dup_len2);
	new_w = ft_strjoin_w_free(new_w, dup_len3);
	free(dup_len2);
	// free(dup_len3);
	save = (*i_expnd);
	while (mn_tmp->word[(*i_expnd)])
		(*i_expnd)++;
	dup_len1 = ft_strdup_len(mn_tmp->word, save, (*i_expnd));
	new_w = ft_strjoin_w_free(new_w, dup_len1);
	// free(dup_len1);
	if (mn_tmp->word[0])
		free(mn_tmp->word);
	mn_tmp->word = new_w;
	// free(new_w);
	// print_word(mn_tmp->word);
	// ft_print_rl_out(mn_sh);
	// printf(BACK_WHITE" -------------------------------------------- "RST"\n\n");
	if (ft_isthere_dollar(mn_tmp->word, mn_sh) == SUCCESS)
		expand(mn_sh);
}

void	expand(t_mini_sh *mini_sh)
{
	t_arr_output	*mini_tmp;
	int				ite_expand;
	int				is_dquote;

	is_dquote = FAIL;
	mini_tmp = mini_sh->rl_out_head;
	while (mini_tmp)
	{
		ite_expand = 0;
		// print_word2(mini_tmp->word);
		if (mini_tmp->word[0])
		{
			// printf(BACK_GREEN"%c"RST"\n\n", mini_tmp->word[ite_expand]);
			while (mini_tmp->word[ite_expand])
			{
				check_qt_open(mini_tmp->word, mini_sh, &ite_expand, &is_dquote);
				if (mini_sh->is_squote == SUCCESS)
				{
					if (mini_tmp->word[ite_expand] == '$')
						ft_replace_dollar(mini_sh, mini_tmp, &ite_expand);
				}
				else if (mini_sh->is_dquote == SUCCESS)
					printf("We have to configure simple quote\n");
				ite_expand++;
			}
		}
		mini_tmp = mini_tmp->next;
		if (!mini_tmp)
			break ;
	}
}

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

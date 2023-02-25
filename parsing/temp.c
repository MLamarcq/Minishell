/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 02:21:41 by gael              #+#    #+#             */
/*   Updated: 2023/02/23 23:31:25 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_isthere_dollar(char *str)
{
	int	ite_isdollar;

	ite_isdollar = -1;
	while (str[++ite_isdollar])
	{
		if (str[ite_isdollar] == '$')
			return (SUCCESS);
	}
	return (FAIL);
}

void	check_qt_open(t_arr_output *mn_tmp, int *i_expnd, int *is_qt)
{
	if (mn_tmp->word[*i_expnd] == D_QUOTE)
	{
		if ((*is_qt) == FAIL)
			(*is_qt) = SUCCESS;
		else
			(*is_qt) = FAIL;
	}
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
	new_w = ft_strjoin(new_w, dup_len1);
	//printf("new -> %s\n", new_w);
	// free(dup_len1);
	if (mn_tmp->word[0])
		free(mn_tmp->word);
	mn_tmp->word = new_w;
	free(new_w);
	// print_word(mn_tmp->word);
	// ft_print_rl_out(mn_sh);
	// printf(BACK_WHITE" -------------------------------------------- "RST"\n\n");
	if (ft_isthere_dollar(mn_tmp->word) == SUCCESS)
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
		while (mini_tmp->word[ite_expand])
		{
			check_qt_open(mini_tmp, &ite_expand, &is_dquote);
			if (is_dquote == SUCCESS)
			{
				if (mini_tmp->word[ite_expand] == '$')
					ft_replace_dollar(mini_sh, mini_tmp, &ite_expand);
			}
			ite_expand++;
		}
		mini_tmp = mini_tmp->next;
	}
}

void	print_word(char *new_w)
{
	int x = 0;
	while (new_w[x])
	{
		printf("%c", new_w[x]);
		x++;
	}
	printf("%i\n", new_w[x]);
}

//changements
// -> expand.c : 
// 		- ligne 73/74 commentees. 
// 		- Conditon if (ft_isthere_dollar(mn_tmp->word) == SUCCESS) copiee ligne 85
// 		- Ligne 69 commentee
 
// -> ft_find_path.c : 
// 		- ligne 36 commentee
// 		- Rajout de "free(var_env)" ligne 113

// -> 
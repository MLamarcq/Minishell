/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggosse <ggosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:52:27 by gael              #+#    #+#             */
/*   Updated: 2023/04/10 16:40:50 by ggosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	count_word_for_alloc(t_mini_sh *mini_sh, t_parse *rlout)
{
	t_parse	*tmp;

	// if (is_sep(mini_sh->rl_out->word) == SUCCESS)
	// 	mini_sh->rl_out = mini_sh->rl_out->next;
	tmp = rlout;
	mini_sh->nbr_word = 0;
	//mini_sh->check_redir = 0;
	if (!tmp)
		return (FAIL);
	if (is_sep(tmp->word) == SUCCESS)
	{
		printf("ici\n");
		// mini_sh->check_redir++;
		tmp = tmp->next;
	}
	while (tmp)
	{
		// if (is_sep(tmp->word) == SUCCESS && is_sep(tmp->next->word) == SUCCESS)
		// 	mini_sh->rl_out = mini_sh->rl_out->next;
		// if (mini_sh->check_redir == 1)
		// {
		// 	printf("break %s\n", tmp->word);
		// 	return (SUCCESS);
		// }
		if (is_sep(tmp->word) == SUCCESS)
			return (SUCCESS);
		mini_sh->nbr_word++;
		if (tmp)
			tmp = tmp->next;
	}
	return (SUCCESS);
}

int    prepare_exec(t_mini_sh *mini_sh)
{
	int    triple;

	if (init_big_tab(mini_sh) == FAIL)
		return (FAIL);
	triple = 0;
	while (mini_sh->rl_out)
	{
		if (count_word_for_alloc(mini_sh, mini_sh->rl_out) == FAIL)
			return (FAIL);
		mini_sh->prepare_exec[triple] = (char **)malloc((sizeof (char *)) * \
		(mini_sh->nbr_word + 1));
		fill_little_tab(mini_sh, triple);
		triple++;
		if (!mini_sh->rl_out->next)
			break ;
		else
		{
			while (is_sep(mini_sh->rl_out->word) == SUCCESS)
				mini_sh->rl_out = mini_sh->rl_out->next;
		}
	}
	mini_sh->prepare_exec[triple] = NULL;
	mini_sh->len_prepare_exec = triple;
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:52:27 by gael              #+#    #+#             */
/*   Updated: 2023/05/02 11:30:48 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	count_word_for_alloc(t_mini_sh *mini_sh, t_parse *rlout)
{
	t_parse	*tmp;

	tmp = rlout;
	mini_sh->nbr_word = 0;
	if (!tmp)
		return (FAIL);
	if (is_sep_int(tmp->type) == SUCCESS)
		tmp = tmp->next;
	while (tmp)
	{
		if (is_sep_int(tmp->type) == SUCCESS)
			return (SUCCESS);
		mini_sh->nbr_word++;
		if (tmp)
			tmp = tmp->next;
	}
	return (SUCCESS);
}

int	prepare_exec(t_mini_sh *mini_sh)
{
	int	triple;

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
			while (is_sep_int(mini_sh->rl_out->type) == SUCCESS)
				mini_sh->rl_out = mini_sh->rl_out->next;
		}
	}
	mini_sh->prepare_exec[triple] = NULL;
	mini_sh->len_prepare_exec = triple;
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:06:13 by mael              #+#    #+#             */
/*   Updated: 2023/03/15 11:50:26 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	fill_little_tab(t_mini_sh *mini_sh, int	trple)
{
	int	dble;

	dble = 0;
	mini_sh->nbr_word = 0;
	while (mini_sh->rl_out && is_sep(mini_sh->rl_out->word) == FAIL)
	{
		mini_sh->prepare_exec[trple][dble] = ft_strdup(mini_sh->rl_out->word);
		dble++;
		if (!mini_sh->rl_out->next)
			break ;
		else
			mini_sh->rl_out = mini_sh->rl_out->next;
	}
	mini_sh->prepare_exec[trple][dble] = NULL;
}

int	init_big_tab(t_mini_sh *mini_sh)
{
	mini_sh->rl_out = mini_sh->rl_out_head;
	if (count_sep_2(mini_sh) == FAIL)
		return (FAIL);
	mini_sh->prepare_exec = (char ***)malloc((sizeof (char **)) * \
	(mini_sh->sep_2 + 2));
	if (!mini_sh->prepare_exec)
		return (FAIL_MALLOC);
	if (is_sep(mini_sh->rl_out->word) == SUCCESS)
		mini_sh->rl_out = mini_sh->rl_out->next;
	return (SUCCESS);
}

// int	init_big_tab(t_mini_sh *mini_sh)
// {
// 	if (count_sep_2(mini_sh) == FAIL)
// 		return (FAIL);
// 	mini_sh->prepare_exec = (char ***)malloc((sizeof (char **)) * 
// 		(mini_sh->sep_2 + 2));
// 	if (!mini_sh->prepare_exec)
// 		return (FAIL_MALLOC);
// 	return (SUCCESS);
// }

// int	fill_little_tab(t_parse *tmp, int *dble, int *triple, t_mini_sh *mini_sh)
// {
// 	while (tmp && is_sep(tmp->word) == FAIL)
// 	{
// 		mini_sh->prepare_exec[(*triple)][(*dble)] = ft_strdup(tmp->word);
// 		(*dble)++;
// 		if (!tmp->next)
// 			break ;
// 		else
// 			tmp = tmp->next;
// 	}
// 	return (SUCCESS);
// } 

// int	init_little_tab(t_mini_sh *mini_sh)
// {
// 	t_parse	*tmp;
// 	int				dble;
// 	int				triple;
	
// 	tmp = mini_sh->rl_out_head;
// 	if (is_sep(tmp->word) == SUCCESS)
// 		tmp = tmp->next;
// 	triple = 0;
// 	while (tmp)
// 	{
// 		if (count_word_for_alloc(mini_sh, tmp) == FAIL)
// 			return (FAIL);
// 		dble = 0;
// 		mini_sh->prepare_exec[triple] = (char **)malloc((sizeof (char *)) * 
// 			(mini_sh->nbr_word + 1));
// 		mini_sh->nbr_word = 0;
// 		fill_little_tab(tmp, &dble, &triple, mini_sh);
// 		// while (tmp && is_sep(tmp->word) == FAIL)
// 		// {
// 		// 	mini_sh->prepare_exec[triple][dble] = ft_strdup(tmp->word);
// 		// 	dble++;
// 		// 	if (!tmp->next)
// 		// 		break ;
// 		// 	else
// 		// 		tmp = tmp->next;
// 		// }
// 		mini_sh->prepare_exec[triple][dble] = NULL;
// 		triple++;
// 		if (!tmp->next)
// 			break ;
// 		else
// 			tmp = tmp->next;
// 	}
// 	mini_sh->prepare_exec[triple] = NULL;
// 	return (SUCCESS);
// }
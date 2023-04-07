/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:01:55 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/04/03 17:01:58 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	if_hr_doc(t_mini_sh *mini_sh)
{
	t_parse *tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == HR_DOC)
		{
			///printf("lol\n");
			// printf(RED"tmp->next = %s"RST"\n", tmp->next->word);
			// printf(RED"tmp->next = %s"RST"\n", tmp->next->next->word);
			if (tmp->next && tmp->next->next && tmp->next->next->word)
				mini_sh->sep_2++;
		}
		tmp = tmp->next;
	}
}
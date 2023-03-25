/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:52:27 by gael              #+#    #+#             */
/*   Updated: 2023/03/25 14:36:12 by mael             ###   ########.fr       */
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

void	free_exec(t_mini_sh *mini_sh)
{
	int		free_third;
	int		free_second;

	free_third = 0;
	while (mini_sh->prepare_exec[free_third])
	{
		free_second = 0;
		while (mini_sh->prepare_exec[free_third][free_second])
		{
			free(mini_sh->prepare_exec[free_third][free_second]);
			mini_sh->prepare_exec[free_third][free_second] = NULL;
			free_second++;
		}
		if (mini_sh->prepare_exec[free_third])
		{
			free(mini_sh->prepare_exec[free_third]);
			mini_sh->prepare_exec[free_third] = NULL;
		}
		mini_sh->prepare_exec[free_third] = NULL;
		free_third++;
	}
	free(mini_sh->prepare_exec);
	mini_sh->prepare_exec = NULL;
}

int	prepare_exec(t_mini_sh *mini_sh)
{
	int	triple;

	if (init_big_tab(mini_sh) == FAIL)
		return (FAIL);
	triple = 0;
	//mini_sh->rl_out = mini_sh->rl_out_head;
	while (mini_sh->rl_out)
	{
		if (count_word_for_alloc(mini_sh, mini_sh->rl_out) == FAIL)
			return (FAIL);
		printf("nbr_words = %d\n", mini_sh->nbr_word);
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
		// if (mini_sh->check_redir == 1)
		//printf("test = %s\n", mini_sh->rl_out->word);
		//mini_sh->rl_out = mini_sh->rl_out->next;
		printf("\n.....................................\n\n");
	}
	mini_sh->prepare_exec[triple] = NULL;
	mini_sh->len_prepare_exec = triple;
	int i = 0;
	int j;
	while (mini_sh->prepare_exec[i])
	{
		j = 0;
		while (mini_sh->prepare_exec[i][j])
		{
			printf("ligne[%d][%d] : %s\n", i, j, mini_sh->prepare_exec[i][j]);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

// ls -l -a | cat > oufile | ls | ls << grep -i >> cat main.c | grep

// int	prepare_exec(t_mini_sh *mini_sh)
// {
// 	t_parse	*tmp;
// 	int				triple;
// 	int				dble;

// 	tmp = mini_sh->rl_out_head;
// 	if (count_sep_2(mini_sh) == FAIL)
// 		return (FAIL);
// 	mini_sh->prepare_exec = (char ***)malloc((sizeof (char **)) * 
// 		(mini_sh->sep_2 + 2));
// 	if (!mini_sh->prepare_exec)
// 		return (FAIL_MALLOC);
// 	return (SUCCESS);
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
// 		while (tmp && is_sep(tmp->word) == FAIL)
// 		{
// 			mini_sh->prepare_exec[triple][dble] = ft_strdup(tmp->word);
// 			dble++;
// 			if (!tmp->next)
// 				break ;
// 			else
// 				tmp = tmp->next;
// 		}
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

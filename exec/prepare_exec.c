/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:52:27 by gael              #+#    #+#             */
/*   Updated: 2023/03/14 12:12:20 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	count_double_arr(t_mini_sh *mini_sh)
{
	t_mini_sh	*mn_tmp;
	int	len_double_arr;

	len_double_arr = 0;
	mn_tmp = mini_sh;
	mn_tmp->rl_out = mini_sh->rl_out_head;
	while (mn_tmp->rl_out)
	{
		if (mn_tmp->rl_out->type == PIPE || mn_tmp->rl_out->type == REDIR_L || mn_tmp->rl_out->type == REDIR_R)
			len_double_arr++;
		mn_tmp->rl_out = mn_tmp->rl_out->next;
	}
	return (len_double_arr);
}

int	count_word_for_alloc(t_mini_sh *mini_sh, t_arr_output *rlout)
{
	t_arr_output *tmp;

	tmp = rlout;
	mini_sh->nbr_word = 0;
	if (!tmp)
		return (FAIL);
	if (is_sep(tmp->word) == SUCCESS)
		tmp = tmp->next;
	while (tmp)
	{
		//printf("word = %s\n", tmp->word);
		//printf("nbr_word = %d\n", mini_sh->nbr_word);
		if (is_sep(tmp->word) == SUCCESS)
		{
			//printf("word in = %s\n", tmp->word);
			return (SUCCESS);
		}
		mini_sh->nbr_word++;
		//printf("nbr_word = %d\n", mini_sh->nbr_word);
		if (tmp)
			tmp = tmp->next;
	}
	//printf("nbr_word = %d\n", mini_sh->nbr_word);
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
		//	if (mini_sh->prepare_exec[free_third][free_second])
		//	{
				free(mini_sh->prepare_exec[free_third][free_second]);
				mini_sh->prepare_exec[free_third][free_second] = NULL;
		//	}
			//mini_sh->prepare_exec[free_third][free_second] = NULL;
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
	t_arr_output	*tmp;
	int				triple;
	int				dble;
	// int				len;

	tmp = mini_sh->rl_out_head;
	if (count_sep_2(mini_sh) == FAIL)
		return (FAIL);
	mini_sh->prepare_exec = (char ***)malloc((sizeof (char **)) * (mini_sh->sep_2 + 2));
	if (!mini_sh->prepare_exec)
		return (FAIL_MALLOC);
	if (is_sep(tmp->word) == SUCCESS)
		tmp = tmp->next;
	triple = 0;
	while (tmp)
	{
		if (count_word_for_alloc(mini_sh, tmp) == FAIL)
			return (FAIL);
		dble = 0;
		mini_sh->prepare_exec[triple] = (char **)malloc((sizeof (char *)) * (mini_sh->nbr_word + 1));
		mini_sh->nbr_word = 0;
		while (tmp && is_sep(tmp->word) == FAIL)
		{
			mini_sh->prepare_exec[triple][dble] = ft_strdup(tmp->word);
			dble++;
			if (!tmp->next)
				break;
			else
				tmp = tmp->next;
		}
		mini_sh->prepare_exec[triple][dble] = NULL;
		triple++;
		if (!tmp->next)
			break;
		else
			tmp = tmp->next;
	}
	mini_sh->prepare_exec[triple] = NULL;

	// len = 0;
	// while (mini_sh->prepare_exec[len])
	// {
	// 	printf(BACK_CYAN"mini_sh->prepare_exec[%i][0]: %s"RST"\n", len, mini_sh->prepare_exec[len][0]);
	// 	len++;
	// }
	//free_exec(mini_sh);
	return (SUCCESS);
}

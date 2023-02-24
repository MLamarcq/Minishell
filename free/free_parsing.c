/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:56:00 by gael              #+#    #+#             */
/*   Updated: 2023/02/23 08:07:34 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

// void	free_parsing(t_mini_sh *mini_sh)
// {
// 	t_mini_sh		*tmp;
// 	t_arr_output	*tmp_readline;

// 	tmp = mini_sh;
// 	if (tmp->output)
// 		free(tmp->output);
// 	while (tmp->rl_out)
// 	{
// 		if (tmp->rl_out->word)
// 			free(tmp->rl_out->word);
// 		tmp->rl_out = tmp->rl_out->next;
// 	}
// 	tmp = mini_sh;
// 	while (tmp->rl_out)
// 	{
// 		tmp_readline = tmp->rl_out;
// 		tmp->rl_out = tmp->rl_out->next;
// 		free(tmp_readline);
// 		tmp_readline = mnini->env;
// 		mnini->env = mnini->env->next;
// 		free(tmp_readline);
// 	}
// 	tmp = mini_sh;
// }

void	free_parsing(t_mini_sh *mini_sh)
{
	t_arr_output	*tmp;

	if (mini_sh->output)
		free(mini_sh->output);

	while (mini_sh->rl_out)
	{
		// printf(BACK_GREEN"mini_sh->rl_out->word: %s"RST"\n", mini_sh->rl_out->word);
		free(mini_sh->rl_out->word);
		tmp = mini_sh->rl_out;
		mini_sh->rl_out = mini_sh->rl_out->next;
		free(tmp);
	}
}

void	free_env(t_mini_sh *mini_sh)
{
	int	ite_free_env;

	ite_free_env = -1;
	while (mini_sh->env[++ite_free_env])
	{
		// printf(BACK_GREEN"mini_sh->env[ite_free_env]: %s"RST"\n", mini_sh->env[ite_free_env]);
		// if (mini_sh->env[ite_free_env][0])
		free(mini_sh->env[ite_free_env]);
	}
	free(mini_sh->env);
}

void	ft_free_all(char *str, char **tab)
{
	int	ite;

	ite = -1;
	if (tab)
	{
		while (tab[++ite])
			free(tab[ite]);
		free(tab);
	}
	if (str)
		free(str);
}

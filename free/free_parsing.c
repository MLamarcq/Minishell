/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:56:00 by gael              #+#    #+#             */
/*   Updated: 2023/03/15 23:44:58 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	ft_lstclear(t_parse **lst)
{
	t_parse	*tmp;

	tmp = NULL;
	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->word);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	free_parsing(t_mini_sh *mini_sh)
{
	if (mini_sh->output)
	{
		free(mini_sh->output);
		mini_sh->rl_out = mini_sh->rl_out_head;
		if (mini_sh->rl_out)
			ft_lstclear(&mini_sh->rl_out);
	}
}

void	free_env(t_mini_sh *mini_sh)
{
	int	ite_free_env;

	ite_free_env = -1;
	while (mini_sh->env[++ite_free_env])
		free(mini_sh->env[ite_free_env]);
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

void	ft_free_var_env(char *var_env, char *res_var_env)
{
	free(var_env);
	free(res_var_env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:12:05 by gael              #+#    #+#             */
/*   Updated: 2023/02/19 14:02:33 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	set_type(t_mini_sh *mini_sh)
{
	mini_sh->rl_out = mini_sh->rl_out_head;
	while (mini_sh->rl_out)
	{
		// printf("ft_find_env(envp, %s, "PATH="): %i\n", mini_sh->rl_out->word, ft_find_env(mini_sh->env, mini_sh->rl_out->word, "PATH="));
		if (ft_find_env(mini_sh->env, mini_sh->rl_out->word) == SUCCESS)
			mini_sh->rl_out->type = CMD;
		else if (ft_strncmp(">", mini_sh->rl_out->word, 1) == 0)
			mini_sh->rl_out->type = REDIR_R;
		else if (ft_strncmp("<", mini_sh->rl_out->word, 1) == 0)
			mini_sh->rl_out->type = REDIR_L;
		else if (ft_strncmp("|", mini_sh->rl_out->word, 1) == 0)
			mini_sh->rl_out->type = PIPE;
		else if (ft_strncmp("-", mini_sh->rl_out->word, 1) == 0)
			mini_sh->rl_out->type = OPTION;
		else if (access(mini_sh->rl_out->word, F_OK) == 0)
			mini_sh->rl_out->type = _FILE;
		else
			mini_sh->rl_out->type = ARG;
		mini_sh->rl_out = mini_sh->rl_out->next;
	}
	(void)mini_sh;
}
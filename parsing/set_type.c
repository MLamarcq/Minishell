/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:12:05 by gael              #+#    #+#             */
/*   Updated: 2023/03/15 23:19:36 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	type_utils_1(t_mini_sh *mini_sh)
{
	if (is_built_in(mini_sh) == SUCCESS)
		mini_sh->rl_out->type = BUILT_IN;
	else if (ft_find_env(mini_sh) == SUCCESS)
	{
		if (access(mini_sh->rl_out->word, F_OK) == 0)
			mini_sh->rl_out->type = CMD_ABS;
		else
			mini_sh->rl_out->type = CMD;
	}
}

int	type_utils_2(t_mini_sh *mini_sh)
{
	if (ft_strncmp(">>", mini_sh->rl_out->word, 1) == 0
		&& mini_sh->rl_out->type == FAIL)
	{
		if (ft_strlen(mini_sh->rl_out->word) == 2)
			mini_sh->rl_out->type = APPEND;
		else
			return (printf("minishell: syntax error with >>"), FAIL);
	}
	else if (ft_strncmp("<<", mini_sh->rl_out->word, 1) == 0
		&& mini_sh->rl_out->type == FAIL)
	{
		if (ft_strlen(mini_sh->rl_out->word) == 2)
			mini_sh->rl_out->type = HR_DOC;
		else
			return (printf("minishell: syntax error with <<"), FAIL);
	}
	return (SUCCESS);
}

int	type_utils_3(t_mini_sh *mini_sh)
{
	if (ft_strncmp(">", mini_sh->rl_out->word, 0) == 0
		&& mini_sh->rl_out->type == FAIL)
	{
		if (ft_strlen(mini_sh->rl_out->word) == 1)
			mini_sh->rl_out->type = REDIR_R;
		else
			return (printf("minishell: syntax error with >"), FAIL);
	}
	else if (ft_strncmp("<", mini_sh->rl_out->word, 0) == 0
		&& mini_sh->rl_out->type == FAIL)
	{
		if (ft_strlen(mini_sh->rl_out->word) == 1)
			mini_sh->rl_out->type = REDIR_L;
		else
			return (printf("minishell: syntax error with <"), FAIL);
	}
	return (SUCCESS);
}

int	type_utils_4(t_mini_sh *mini_sh)
{
	if (ft_strncmp("|", mini_sh->rl_out->word, 0) == 0
		&& mini_sh->rl_out->type == FAIL)
	{
		if (ft_strlen(mini_sh->rl_out->word) == 1)
			mini_sh->rl_out->type = PIPE;
		else
			return (printf("minishell: syntax error with |"), FAIL);
	}
	else if (ft_strncmp("-", mini_sh->rl_out->word, 0) == 0
		&& mini_sh->rl_out->type == FAIL)
		mini_sh->rl_out->type = OPTION;
	else if (access(mini_sh->rl_out->word, F_OK) == 0
		&& mini_sh->rl_out->type == FAIL)
		mini_sh->rl_out->type = _FILE;
	else if (mini_sh->rl_out->type == FAIL)
		mini_sh->rl_out->type = ARG;
	return (SUCCESS);
}

int	set_type(t_mini_sh *mini_sh)
{
	mini_sh->rl_out = mini_sh->rl_out_head;
	while (mini_sh->rl_out)
	{
		mini_sh->rl_out->type = FAIL;
		type_utils_1(mini_sh);
		if (type_utils_2(mini_sh) == FAIL)
			return (FAIL);
		if (type_utils_3(mini_sh) == FAIL)
			return (FAIL);
		if (type_utils_4(mini_sh) == FAIL)
			return (FAIL);
		if (!mini_sh->rl_out->next)
			break ;
		mini_sh->rl_out = mini_sh->rl_out->next;
	}
	return (SUCCESS);
}

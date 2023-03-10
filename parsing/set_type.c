/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:12:05 by gael              #+#    #+#             */
/*   Updated: 2023/03/10 10:42:47 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	is_built_in(t_mini_sh *mini_sh)
{
	if (ft_strncmp(mini_sh->rl_out->word, "pwd", ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(mini_sh->rl_out->word, "cd", ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(mini_sh->rl_out->word, "echo", ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(mini_sh->rl_out->word, "unset", ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(mini_sh->rl_out->word, "env", ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(mini_sh->rl_out->word, "export", ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(mini_sh->rl_out->word, "echo", ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	else if (ft_strncmp(mini_sh->rl_out->word, "exit", ft_strlen(mini_sh->rl_out->word)) == 0)
		return (SUCCESS);
	return (FAIL);
}

int	set_type(t_mini_sh *mini_sh)
{
	mini_sh->rl_out = mini_sh->rl_out_head;
	while (mini_sh->rl_out)
	{
		// printf("ft_find_env(envp, %s, "PATH="): %i\n", mini_sh->rl_out->word, ft_find_env(mini_sh->env, mini_sh->rl_out->word, "PATH="));
		if (is_built_in(mini_sh) == SUCCESS)
			mini_sh->rl_out->type = BUILT_IN;
		else if (ft_find_env(mini_sh) == SUCCESS)
		{
			if (access(mini_sh->rl_out->word, F_OK) == 0)
				mini_sh->rl_out->type = CMD_ABS;
			else
				mini_sh->rl_out->type = CMD;
		}
		else if (ft_strncmp(">>", mini_sh->rl_out->word, 2) == 0)
			mini_sh->rl_out->type = APPEND;
		else if (ft_strncmp("<<", mini_sh->rl_out->word, 2) == 0)
			mini_sh->rl_out->type = HR_DOC;
		else if (ft_strncmp(">", mini_sh->rl_out->word, 1) == 0)
		{
			if (ft_strlen(mini_sh->rl_out->word) == 1)
				mini_sh->rl_out->type = REDIR_R;
			else
				return (printf("syntax error with >") ,FAIL);
		}
		else if (ft_strncmp("<", mini_sh->rl_out->word, 1) == 0)
		{
			if (ft_strlen(mini_sh->rl_out->word) == 1)
				mini_sh->rl_out->type = REDIR_L;
			else
				return (printf("syntax error with <") ,FAIL);
		}
		else if (ft_strncmp("|", mini_sh->rl_out->word, 1) == 0)
		{
			if (ft_strlen(mini_sh->rl_out->word) == 1)
				mini_sh->rl_out->type = PIPE;
			else
				return (printf("syntax error with |") ,FAIL);
		}
		else if (ft_strncmp("-", mini_sh->rl_out->word, ft_strlen(mini_sh->rl_out->word)) == 0)
			mini_sh->rl_out->type = OPTION;
		else if (access(mini_sh->rl_out->word, F_OK) == 0)
			mini_sh->rl_out->type = _FILE;
		else
			mini_sh->rl_out->type = ARG;
		if (!mini_sh->rl_out->next)
			break ;
		mini_sh->rl_out = mini_sh->rl_out->next;
	}
	(void)mini_sh;
	return (SUCCESS);
}

// void	set_type(t_mini_sh *mini_sh)
// {
// 	// t_mini_sh *mini_tmp;

// 	// mini_tmp = mini_sh;
// 	mini_sh
// 	while (mini_tmp->rl_out)
// 	{
// 		// printf("ft_find_env(envp, %s, "PATH="): %i\n", mini_tmp->rl_out->word, ft_find_env(mini_tmp->env, mini_tmp->rl_out->word, "PATH="));
// 		if (ft_find_env(mini_tmp->env, mini_tmp->rl_out->word) == SUCCESS)
// 			mini_tmp->rl_out->type = CMD;
// 		else if (ft_strncmp(">", mini_tmp->rl_out->word, 1) == 0)
// 			mini_tmp->rl_out->type = REDIR_R;
// 		else if (ft_strncmp("<", mini_tmp->rl_out->word, 1) == 0)
// 			mini_tmp->rl_out->type = REDIR_L;
// 		else if (ft_strncmp("|", mini_tmp->rl_out->word, 1) == 0)
// 			mini_tmp->rl_out->type = PIPE;
// 		else if (ft_strncmp("-", mini_tmp->rl_out->word, 1) == 0)
// 			mini_tmp->rl_out->type = OPTION;
// 		else if (access(mini_tmp->rl_out->word, F_OK) == 0)
// 			mini_tmp->rl_out->type = _FILE;
// 		else
// 			mini_tmp->rl_out->type = ARG;
// 		mini_tmp->rl_out = mini_tmp->rl_out->next;
// 	}
// 	(void)mini_tmp;
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_sep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:29:33 by mael              #+#    #+#             */
/*   Updated: 2023/04/07 16:45:28 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	init_exec(t_mini_sh *mini_sh)
{
	mini_sh->exec = malloc(sizeof(t_exec_t));
	if (!mini_sh->exec)
		return (FAIL_MALLOC);
	mini_sh->exec->pipe_id = 0;
	mini_sh->exec->nbr_fd_r = 0;
	mini_sh->exec->check_r = 0;
	mini_sh->exec->ana_r = 0;
	mini_sh->exec->nbr_fd_l = 0;
	mini_sh->exec->check_l = 0;
	mini_sh->exec->nbr_fd_hr = 0;
	mini_sh->exec->check_hr = 0;
	mini_sh->exec->nbr_fd_app = 0;
	mini_sh->exec->check_app = 0;
	mini_sh->exec->ana_app = 0;
	mini_sh->exec->fd[0] = 0;
	mini_sh->exec->fd[1] = 0;
	return (SUCCESS);
}

// int	if_redir_r(t_mini_sh *mini_sh, int i_exec)
// {
// 	t_parse	*tmp;

// 	tmp = mini_sh->rl_out_head;
// 	while (tmp)
// 	{
// 		if (tmp->type == REDIR_R)
// 		{
// 			tmp = tmp->next;
// 			if (opendir(tmp->word) != NULL)
// 			{
// 				printf("minishell: %s: Is a directory\n", tmp->word);
// 				return (FAIL);
// 			}
// 			else if (tmp->type == _FILE || tmp->type == CMD_ABS)
// 			{
// 				if (access(tmp->word, W_OK) == -1)
// 				{
// 					printf("minishell: %s: permission denied\n", tmp->word);
// 					return (FAIL);
// 				}
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	(void)i_exec;
// 	return (SUCCESS);
// }

// int	if_redir_l(t_mini_sh *mini_sh)
// {
// 	t_parse	*tmp;

// 	tmp = mini_sh->rl_out_head;
// 	if (init_exec(mini_sh) < 0)
// 		return (FAIL);
// 	if (tmp->type == REDIR_L)
// 	{
// 		tmp = tmp->next;
// 		mini_sh->exec->fd_l = open(tmp->word, O_RDONLY, 0777);
// 		if (!mini_sh->exec->fd_l)
// 		{
// 			printf("Failure during opening the file");
// 			return (FAIL);
// 		}
// 	}
// 	return (SUCCESS);
// }

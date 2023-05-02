/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:20:35 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/05/02 17:39:41 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	start_to_alloc(t_mini_sh *mini_sh)
{
	mini_sh->exec->tab_fd = NULL;
	mini_sh->exec->tab_fd = malloc(sizeof(int *) * (mini_sh->sep_2 + 1));
	if (!mini_sh->exec->tab_fd)
		return (FAIL_MALLOC);
	mini_sh->exec->tab_fd[mini_sh->sep_2] = 0;
	return (SUCCESS);
}

int	fill_fd_tab(t_mini_sh *mini_sh, int i_init_fd, t_parse **tmp)
{
	while ((*tmp))
	{
		if (!(*tmp))
			break ;
		while ((*tmp) && is_sep_int((*tmp)->type) == FAIL)
			(*tmp) = (*tmp)->next;
		if (!(*tmp))
			break ;
		mini_sh->exec->tab_fd[i_init_fd] = malloc(sizeof(int) * 3);
		mini_sh->exec->tab_fd[i_init_fd][2] = 0;
		if (pipe(mini_sh->exec->tab_fd[i_init_fd]) == -1)
			return (printf("pipe not working\n"), FAIL);
		if ((*tmp) && (*tmp)->type == PIPE && \
		is_sep_int((*tmp)->next->type) == SUCCESS)
		{
			close(mini_sh->exec->tab_fd[i_init_fd][0]);
			mini_sh->exec->tab_fd[i_init_fd][0] = 0;
			(*tmp) = (*tmp)->next;
		}
		if ((*tmp))
			count_redir_for_alloc((*tmp), mini_sh);
		i_init_fd++;
		(*tmp) = (*tmp)->next;
	}
	return (SUCCESS);
}

int	init_tab_fd(t_mini_sh *mini_sh)
{
	int		i_init_fd;
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	i_init_fd = 0;
	if (start_to_alloc(mini_sh) < 0)
		return (FAIL);
	if (fill_fd_tab(mini_sh, i_init_fd, &tmp) < 0)
		return (FAIL);
	init_redir_fd(mini_sh);
	return (SUCCESS);
}

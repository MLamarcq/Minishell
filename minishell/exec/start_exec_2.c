/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:33:14 by mael              #+#    #+#             */
/*   Updated: 2023/05/02 15:51:39 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

int	init_sep_type(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	int		i;

	tmp = mini_sh->rl_out_head;
	free_sep_type(mini_sh);
	if (mini_sh->redir_alone && mini_sh->redir_alone == SUCCESS)
		mini_sh->sep_type = (int *)malloc(sizeof(int) * (2));
	else
		mini_sh->sep_type = (int *)malloc(sizeof(int) * (mini_sh->sep_2 + 1));
	if (!mini_sh->sep_type)
		return (FAIL_MALLOC);
	i = 0;
	while (tmp)
	{
		if (is_sep_int(tmp->type) == SUCCESS && tmp->type && i < mini_sh->sep_2)
			mini_sh->sep_type[i++] = tmp->type;
		tmp = tmp->next;
	}
	mini_sh->sep_type[i] = FAIL;
	mini_sh->sep_id = 0;
	return (SUCCESS);
}

int	start_exec(t_mini_sh *mini_sh)
{
	int	i_exec;

	i_exec = 0;
	g_exit_stt = 0;
	mini_sh->pids = (pid_t *)malloc((sizeof (pid_t)) * (mini_sh->sep_2 + 1));
	if (!mini_sh->pids)
		return (FAIL_MALLOC);
	mini_sh->rl_check_redir = mini_sh->rl_out_head;
	if (mini_sh->exec->nbr_fd_hr > 0)
		exec_all_hr_doc(mini_sh);
	if (execution(mini_sh, i_exec) == FAIL)
		return (FAIL);
	ft_parent(mini_sh, &i_exec);
	return (SUCCESS);
}

int	execution(t_mini_sh *mini_sh, int i_exec)
{
	while (mini_sh->prepare_exec[i_exec])
	{
		if (g_exit_stt == 130)
			return (FAIL);
		if (exec_builtin(mini_sh, i_exec) == FAIL)
		{
			mini_sh->pids[i_exec] = fork();
			if (mini_sh->pids[i_exec] == -1)
				return (FAIL);
			if (mini_sh->pids[i_exec] == 0)
				child_process(mini_sh, i_exec);
		}
		else
			mini_sh->pids[i_exec] = FAIL;
		if (mini_sh->sep_type && i_exec < mini_sh->sep_2 \
		&& i_exec < mini_sh->len_prepare_exec - 2)
			increase_check(mini_sh, mini_sh->sep_type[i_exec]);
		i_exec++;
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:33:14 by mael              #+#    #+#             */
/*   Updated: 2023/05/02 08:31:09 by gael             ###   ########.fr       */
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
		if (is_sep(tmp->word) == SUCCESS && tmp->type && i < mini_sh->sep_2)
			mini_sh->sep_type[i++] = tmp->type;
		tmp = tmp->next;
	}
	mini_sh->sep_type[i] = FAIL;
	mini_sh->sep_id = 0;
	return (SUCCESS);
}

int	middle_tab_fd(t_mini_sh *mini_sh, t_parse *tmp, int i_init_fd)
{
	if (!tmp)
		return (0);
	while (tmp && is_sep_int(tmp->type) == FAIL)
		tmp = tmp->next;
	if (!tmp)
		return (0);
	mini_sh->exec->tab_fd[i_init_fd] = malloc(sizeof(int) * 3);
	mini_sh->exec->tab_fd[i_init_fd][2] = 0;
	if (pipe(mini_sh->exec->tab_fd[i_init_fd]) == -1)
		return (printf("pipe not working\n"), FAIL);
	if (tmp && tmp->type == PIPE && is_sep_int(tmp->next->type) == SUCCESS)
	{
		close(mini_sh->exec->tab_fd[i_init_fd][0]);
		mini_sh->exec->tab_fd[i_init_fd][0] = 0;
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	start_tab_fd(t_mini_sh *mini_sh, int *i_init_fd)
{
	(*i_init_fd) = 0;
	mini_sh->exec->tab_fd = NULL;
	mini_sh->exec->tab_fd = malloc(sizeof(int *) * (mini_sh->sep_2 + 1));
	if (!mini_sh->exec->tab_fd)
		return (FAIL_MALLOC);
	return (SUCCESS);
}

int	init_tab_fd(t_mini_sh *mini_sh)
{
	int		i_init_fd;
	int		res;
	t_parse	*tmp;

	res = -42;
	tmp = mini_sh->rl_out_head;
	start_tab_fd(mini_sh, &i_init_fd);
	mini_sh->exec->tab_fd[mini_sh->sep_2] = 0;
	while (tmp)
	{
		res = middle_tab_fd(mini_sh, tmp, i_init_fd);
		if (res == FAIL)
			return (FAIL);
		else if (res == 0)
			break ;
		if (tmp)
			count_redir_for_alloc(tmp, mini_sh);
		i_init_fd++;
		tmp = tmp->next;
	}
	init_redir_fd(mini_sh);
	return (SUCCESS);
}

int	exec_builtin(t_mini_sh *mini_sh, int i)
{
	if (mini_sh->len_prepare_exec == 1)
	{
		if (do_built_in(mini_sh, i) == FAIL)
			return (FAIL);
		else
			return (SUCCESS);
	}
	return (FAIL);
}

int	exec_redir(t_mini_sh *mini, int i_exec)
{
	if (i_exec < mini->sep_2 && mini->sep_type \
	&& mini->sep_type[i_exec] != FAIL && mini->sep_type[i_exec] == RDR_R)
		do_redir_r(mini, i_exec);
	else if (i_exec < mini->sep_2 && mini->sep_type \
	&& mini->sep_type[i_exec] != FAIL && mini->sep_type[i_exec] == APPEND)
		do_append(mini, i_exec);
	else if (i_exec < mini->sep_2 && mini->sep_type \
	&& mini->sep_type[i_exec] != FAIL && mini->sep_type[i_exec] == HR_DOC)
		do_heredoc_redir(mini, i_exec);
	else if (i_exec < mini->sep_2 && mini->sep_type \
	&& mini->sep_type[i_exec] != FAIL && mini->sep_type[i_exec] == RDR_L)
		do_redir_l(mini, i_exec);
	return (SUCCESS);
}

int	is_there_a_redir(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type && is_sep_int(tmp->type) == SUCCESS && tmp->type != PIPE)
			return (SUCCESS);
		tmp = tmp->next;
	}
	return (FAIL);
}

int	first_is_a_redir(t_mini_sh *mini_sh)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	if (is_all(tmp->type) == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

int	count_redir_in_line(t_mini_sh *mini_sh, int type)
{
	t_parse	*temp;

	while (mini_sh->rl_check_redir)
	{
		if (mini_sh->rl_check_redir->type == type)
		{
			temp = mini_sh->rl_check_redir->next;
			while (temp)
			{
				if (is_sep(temp->word) == SUCCESS)
				{
					if (temp->type == type)
						return (SUCCESS);
					else
						return (FAIL);
				}
				temp = temp->next;
			}
		}
		mini_sh->rl_check_redir = mini_sh->rl_check_redir->next;
	}
	return (SUCCESS);
}

void	increase_check(t_mini_sh *mini_sh, int type)
{
	if (type == RDR_R)
	{
		if (mini_sh->exec->check_r < mini_sh->exec->nbr_fd_r && \
		count_redir_in_line(mini_sh, type) == FAIL)
			mini_sh->exec->check_r++;
	}
	else if (type == APPEND)
	{
		if (mini_sh->exec->check_app < mini_sh->exec->nbr_fd_app && \
		count_redir_in_line(mini_sh, type) == FAIL)
			mini_sh->exec->check_app++;
	}
	else if (type == HR_DOC)
	{
		if (mini_sh->exec->check_hr < mini_sh->exec->nbr_fd_hr && \
		count_redir_in_line(mini_sh, type) == FAIL)
			mini_sh->exec->check_hr++;
	}
	else if (type == RDR_L)
	{
		if (mini_sh->exec->check_l < mini_sh->exec->nbr_fd_l && \
		count_redir_in_line(mini_sh, type) == FAIL)
			mini_sh->exec->check_l++;
	}
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
	while (mini_sh->prepare_exec[i_exec])
	{
		if (g_exit_stt == 130)
			return (FAIL);
		if (exec_builtin(mini_sh, i_exec) == FAIL)
		{
			if (do_exec(mini_sh, i_exec) == FAIL)
				return (FAIL);
		}
		else
			mini_sh->pids[i_exec] = FAIL;
		if (mini_sh->sep_type && i_exec < mini_sh->sep_2 \
		&& i_exec < mini_sh->len_prepare_exec - 2)
			increase_check(mini_sh, mini_sh->sep_type[i_exec]);
		i_exec++;
	}
	ft_parent(mini_sh, &i_exec);
	return (SUCCESS);
}

int	do_exec(t_mini_sh *mini_sh, int i_exec)
{
	mini_sh->pids[i_exec] = fork();
	if (mini_sh->pids[i_exec] == -1)
		return (FAIL);
	if (mini_sh->pids[i_exec] == 0)
		child_process(mini_sh, i_exec);
	return (SUCCESS);
}

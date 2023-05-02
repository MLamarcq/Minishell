/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:57:24 by ggosse            #+#    #+#             */
/*   Updated: 2023/05/02 08:34:33 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

void	analyse_hrdoc_before_alloc(t_mini_sh *mini_sh, t_parse *tmp)
{
	t_parse	*temp;

	temp = tmp;
	if (temp->type == HR_DOC)
	{
		temp = temp->next;
		while (temp)
		{
			if (temp->type == HR_DOC)
			{
				mini_sh->exec->ana_hr = 1;
				break ;
			}
			else if (temp->type == PIPE)
			{
				mini_sh->exec->ana_hr = 0;
				break ;
			}
			temp = temp->next;
		}
	}
}

void	change_hr_doc(t_mini_sh *mini_sh)
{
	int		check;
	t_parse	*tmp;
	t_parse	*temp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		check = 0;
		if (tmp->type == HR_DOC)
		{
			temp = tmp->next;
			while (temp)
			{
				if (change_nbr_hr_util(mini_sh, temp, &check) == SUCCESS)
					break ;
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
}

int	init_hr_dc_tab(t_mini_sh *m)
{
	int		i;
	t_parse	*tmp;

	tmp = m->rl_out_head;
	i = -1;
	if (malloc_hrdoc_tab(m) != SUCCESS)
		return (FAIL);
	while (++i < m->exec->nbr_fd_hr)
	{
		while (tmp)
		{
			if (tmp->type == HR_DOC)
			{
				m->exec->hr_name[i] = ft_strjoin_rfree(".heredoc", ft_itoa(i));
				m->exec->fd_hr[i] = \
				open(m->exec->hr_name[i], O_WRONLY | O_CREAT, 0644);
				if (m->exec->fd_hr[i] == -1)
					return (FAIL);
				tmp = tmp->next;
				break ;
			}
			tmp = tmp->next;
		}
	}
	return (SUCCESS);
}

int	malloc_hrdoc_tab(t_mini_sh *mini_sh)
{
	mini_sh->exec->fd_hr = malloc(sizeof(int) * mini_sh->exec->nbr_fd_hr + 1);
	if (!mini_sh->exec->fd_hr)
		return (FAIL_MALLOC);
	mini_sh->exec->hr_name = malloc(sizeof(char *) * \
	(mini_sh->exec->nbr_fd_hr + 1));
	if (!mini_sh->exec->hr_name)
		return (FAIL_MALLOC);
	mini_sh->exec->hr_name[mini_sh->exec->nbr_fd_hr] = 0;
	return (SUCCESS);
}

void	do_heredoc(t_mini_sh *mini_sh, int i, t_parse *tmp)
{
	char	*input;

	exec_signal(2);
	while (1)
	{
		input = readline(">");
		if (handle_input_hrdoc(mini_sh, tmp, &input) == SUCCESS)
			break ;
		hrdoc_expand(mini_sh, &input);
		ft_putstr_fd(input, mini_sh->exec->fd_hr[i]);
		write(mini_sh->exec->fd_hr[i], "\n", 1);
		free(input);
	}
}

int	handle_input_hrdoc(t_mini_sh *mini_sh, t_parse *tmp, char **input)
{
	if (g_exit_stt == 130)
	{
		free((*input));
		close_all(mini_sh);
		free_all(mini_sh);
		exit(130);
	}
	if (!(*input))
	{
		printf("minishell: warning: here-document delimited");
		printf(" by end-of-file (wanted '%s')\n", tmp->next->word);
		free((*input));
		return (SUCCESS);
	}
	if (ft_strncmp((*input), tmp->next->word, ft_strlen(tmp->next->word)) == 0)
	{
		free((*input));
		return (SUCCESS);
	}
	return (FAIL);
}

int	exec_all_hr_doc(t_mini_sh *mini_sh)
{
	int		i;
	pid_t	child;
	t_parse	*tmp;

	i = 0;
	tmp = mini_sh->rl_out_head;
	child = fork();
	if (child == -1)
		return (FAIL);
	if (child == 0)
		child_hrdoc(mini_sh, tmp, &i);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(child, &g_exit_stt, 0);
		if (WIFEXITED(g_exit_stt))
		{
			g_exit_stt = WEXITSTATUS(g_exit_stt);
		}
		exec_signal(1);
	}
	return (SUCCESS);
}

void	child_hrdoc(t_mini_sh *mini_sh, t_parse *tmp, int *i)
{
	while (tmp)
	{
		if (tmp->type == HR_DOC && (*i) < mini_sh->exec->nbr_fd_hr)
			do_heredoc(mini_sh, (*i)++, tmp);
		tmp = tmp->next;
	}
	close_all(mini_sh);
	free_all(mini_sh);
	exit (0);
}

int	is_last_read(t_mini_sh *mini_sh, int i_last_read)
{
	if (mini_sh->sep_type && mini_sh->sep_type[i_last_read - 1] \
	&& mini_sh->sep_type[i_last_read - 1] == RDR_L)
		mini_sh->exec->fd_in = mini_sh->exec->fd_l[mini_sh->exec->check_l];
	else if (mini_sh->sep_type && mini_sh->sep_type[i_last_read - 1] \
	&& mini_sh->sep_type[i_last_read - 1] == HR_DOC && \
	mini_sh->exec->fd_hr[i_last_read - 1])
	{
		if (mini_sh->exec->fd_hr[i_last_read - 1])
			close (mini_sh->exec->fd_hr[i_last_read - 1]);
		mini_sh->exec->fd_hr[i_last_read - 1] = \
		open(mini_sh->exec->hr_name[i_last_read - 1], O_RDONLY, 0644);
		if (!mini_sh->exec->hr_name[i_last_read - 1])
			return (FAIL);
		mini_sh->exec->fd_in = mini_sh->exec->fd_hr[i_last_read - 1];
	}
	return (SUCCESS);
}

void	go_to_last_read(t_mini_sh *mini_sh, int i_exec)
{
	int	i_last_read;
	int	check;

	i_last_read = i_exec;
	check = 0;
	while (mini_sh->sep_type[i_last_read] && \
	(issep_write(mini_sh->sep_type[i_last_read]) == FAIL || \
	mini_sh->sep_type[i_last_read] != FAIL) && (i_last_read < (mini_sh->sep_2)))
	{
		if (issep_read(mini_sh->sep_type[i_last_read]) == SUCCESS)
			check = 1;
		i_last_read++;
	}
	if (check == 1)
	{
		if (is_last_read(mini_sh, i_last_read) == FAIL)
			return ;
	}
}

int	one_l_multi_hr(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	int		l_check;
	int		hr_check;

	l_check = FAIL;
	hr_check = FAIL;
	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == RDR_L)
		{
			l_check = SUCCESS;
			break ;
		}
		tmp = tmp->next;
	}
	second_part_hr_multi(tmp, &hr_check);
	if (l_check == SUCCESS && hr_check == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

void	second_part_hr_multi(t_parse *tmp, int *hr_check)
{
	while (tmp)
	{
		if (tmp->type == HR_DOC && tmp->next && \
		tmp->next->next && tmp->next->next->type == HR_DOC)
		{
			(*hr_check) = SUCCESS;
			break ;
		}
		tmp = tmp->next;
	}
}

void	do_heredoc_redir(t_mini_sh *mini_sh, int i_exec)
{
	close (mini_sh->exec->fd_hr[mini_sh->exec->check_hr]);
	mini_sh->exec->fd_hr[mini_sh->exec->check_hr] = \
	open(mini_sh->exec->hr_name[mini_sh->exec->check_hr], O_RDONLY, 0644);
	if (mini_sh->sep_2 && mini_sh->sep_type && \
	(mini_sh->sep_2 == 1 || !mini_sh->sep_type[i_exec + 1]))
		close(mini_sh->exec->tab_fd[i_exec][1]);
	mini_sh->exec->fd_in = mini_sh->exec->fd_hr[mini_sh->exec->check_hr];
	if (mini_sh->sep_type && do_good_redir_l(mini_sh, \
	i_exec) == SUCCESS && one_l_multi_hr(mini_sh) == FAIL)
	{
		go_to_last_read(mini_sh, i_exec);
		mini_sh->exec->fd_out = 1;
	}
	else if (mini_sh->sep_type[i_exec + 1] && \
	mini_sh->sep_type[i_exec + 1] != FAIL)
	{
		go_to_last_read(mini_sh, i_exec);
		do_good_redir(mini_sh, i_exec);
	}
	else
	{
		close(mini_sh->exec->tab_fd[i_exec][1]);
		mini_sh->exec->fd_out = 1;
	}
}

void	unlink_hr_dc(t_mini_sh *mini_sh)
{
	int	i;

	i = 0;
	while (i < mini_sh->exec->nbr_fd_hr)
	{
		unlink(mini_sh->exec->hr_name[i]);
		i++;
	}
}

void	free_hr_doc(t_mini_sh *mini_sh)
{
	if (mini_sh->exec->nbr_fd_hr > 0)
		free(mini_sh->exec->fd_hr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:57:24 by ggosse            #+#    #+#             */
/*   Updated: 2023/05/02 17:47:21 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

int	handle_input(t_mini_sh *mini_sh, t_parse *tmp, char **input)
{
	(*input) = readline("> ");
	if (g_exit_stt == 130)
	{
		close_all(mini_sh);
		free_all(mini_sh);
		exit(130);
	}
	if (!(*input))
	{
		printf("minishell: warning: here-document delimited");
		printf(" by end-of-file (wanted '%s')\n", tmp->next->word);
		return (FAIL);
	}
	if (ft_strncmp((*input), tmp->next->word, ft_strlen(tmp->next->word)) == 0)
	{
		free((*input));
		return (FAIL);
	}
	return (SUCCESS);
}

void	do_heredoc(t_mini_sh *mini_sh, int i, t_parse *tmp)
{
	char	*input;

	input = NULL;
	exec_signal(2);
	while (1)
	{
		if (handle_input(mini_sh, tmp, &input) == FAIL)
			break ;
		hrdoc_expand(mini_sh, &input);
		ft_putstr_fd(input, mini_sh->exec->fd_hr[i]);
		write(mini_sh->exec->fd_hr[i], "\n", 1);
		free(input);
	}
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
		child_hrdoc(mini_sh, tmp, i);
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

void	child_hrdoc(t_mini_sh *mini_sh, t_parse *tmp, int i)
{
	while (tmp)
	{
		if (tmp->type == HR_DOC)
		{
			if (i < mini_sh->exec->nbr_fd_hr)
			{
				do_heredoc(mini_sh, i, tmp);
				i++;
			}
		}
		tmp = tmp->next;
	}
	close_all(mini_sh);
	free_all(mini_sh);
	exit (0);
}

int	middle_last_read(t_mini_sh *mini_sh, int i_last_read, int check)
{
	if (check == 1)
	{
		if (mini_sh->sep_type && mini_sh->sep_type[i_last_read - 1] \
		&& mini_sh->sep_type[i_last_read - 1] == REDIR_L)
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
	}
	return (SUCCESS);
}

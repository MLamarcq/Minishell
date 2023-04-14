/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:57:24 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/14 14:31:05 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	init_hr_dc_tab(t_mini_sh *mini_sh)
{
	int		i;
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	i = 0;
	mini_sh->exec->fd_hr = malloc(sizeof(int) * mini_sh->exec->nbr_fd_hr + 1);
	if (!mini_sh->exec->fd_hr)
		return (FAIL_MALLOC);
	mini_sh->exec->fd_hr[mini_sh->exec->nbr_fd_hr] = 0;
	mini_sh->exec->hr_name = malloc(sizeof(char * ) * (mini_sh->exec->nbr_fd_hr + 1));
	if (!mini_sh->exec->hr_name)
		return (FAIL_MALLOC);
	mini_sh->exec->hr_name[mini_sh->exec->nbr_fd_hr] = 0;
	while (i < mini_sh->exec->nbr_fd_hr)
	{
		while (tmp)
		{
			if (tmp->type == HR_DOC)
			{
				mini_sh->exec->hr_name[i] = ft_strjoin_rfree(".heredoc", ft_itoa(i));
				mini_sh->exec->fd_hr[i] = open(mini_sh->exec->hr_name[i], O_WRONLY | O_CREAT , 0644);
				printf(GREEN"fd_hr[%i] == %d\t%s"RST"\n", i, mini_sh->exec->fd_hr[i], tmp->next->word);
				if (mini_sh->exec->fd_hr[i] == -1)
					return (FAIL);
				tmp = tmp->next;
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (SUCCESS);
}

void	do_heredoc(t_mini_sh *mini_sh, int i, t_parse *tmp)
{
	char	*input;

	while (1)
	{
		input = readline("&>");
		if (ft_strncmp(input, tmp->next->word, ft_strlen(tmp->next->word)) == 0)
			break ;
		ft_putstr_fd(input, mini_sh->exec->fd_hr[i]);
		write(mini_sh->exec->fd_hr[i], "\n", 1);
	}
}


int	exec_all_hr_doc(t_mini_sh *mini_sh)
{
	int		i;
	t_parse	*tmp;

	i = 0;
	tmp = mini_sh->rl_out_head;
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
	return (SUCCESS);
}

void	do_heredoc_redir(t_mini_sh *mini_sh, int i_exec)
{
	close (mini_sh->exec->fd_hr[mini_sh->exec->check_hr]);
	mini_sh->exec->fd_hr[mini_sh->exec->check_hr] = \
	open(mini_sh->exec->hr_name[mini_sh->exec->check_hr], O_RDONLY, 0644);
	if (mini_sh->sep_2 == 1 || !mini_sh->sep_type[i_exec + 1])
		close(mini_sh->exec->tab_fd[i_exec][1]);
	mini_sh->exec->fd_in = mini_sh->exec->fd_hr[mini_sh->exec->check_hr];
	if (mini_sh->sep_type[i_exec + 1])
	{
		if (mini_sh->sep_type[i_exec + 1] == PIPE)
			mini_sh->exec->fd_out = mini_sh->exec->tab_fd[i_exec + 1][1];
		else if (mini_sh->sep_type[i_exec + 1] == REDIR_R)
			mini_sh->exec->fd_out = mini_sh->exec->fd_r[mini_sh->exec->check_r];
		else if (mini_sh->sep_type[i_exec + 1] == APPEND)
			mini_sh->exec->fd_out = \
			mini_sh->exec->fd_app[mini_sh->exec->check_app];
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

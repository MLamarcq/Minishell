/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:57:24 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/24 13:45:34 by mlamarcq         ###   ########.fr       */
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
				if (is_sep(temp->word) == SUCCESS)
				{
					if (temp->type == HR_DOC)
						check = 1;
					if (check == 1)
						mini_sh->exec->nbr_fd_hr = mini_sh->exec->nbr_fd_hr - 1;
					break ;
				}
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
}


int	init_hr_dc_tab(t_mini_sh *mini_sh)
{
	int i;
	t_parse *tmp;

	tmp = mini_sh->rl_out_head;
	i = 0;
	mini_sh->exec->fd_hr = malloc(sizeof(int) * mini_sh->exec->nbr_fd_hr + 1);
	if (!mini_sh->exec->fd_hr)
		return (FAIL_MALLOC);
	//change_hr_doc(mini_sh);
	printf(BOLD_GREEN"nbr_hr_doc = %d"RST"\n", mini_sh->exec->nbr_fd_hr);
	// mini_sh->exec->fd_hr[mini_sh->exec->nbr_fd_hr] = 0;
	mini_sh->exec->hr_name = malloc(sizeof(char *) * (mini_sh->exec->nbr_fd_hr + 1));
	if (!mini_sh->exec->hr_name)
		return (FAIL_MALLOC);
	mini_sh->exec->hr_name[mini_sh->exec->nbr_fd_hr] = 0;
	while (i < mini_sh->exec->nbr_fd_hr)
	{
		while (tmp)
		{
			if (tmp->type == HR_DOC)
			{
				analyse_hrdoc_before_alloc(mini_sh, tmp);
				mini_sh->exec->hr_name[i] = ft_strjoin_rfree(".heredoc", ft_itoa(i));
				mini_sh->exec->fd_hr[i] = open(mini_sh->exec->hr_name[i], O_WRONLY | O_CREAT , 0644);
				if (mini_sh->exec->fd_hr[i] == -1)
					return (FAIL);
				printf(GREEN"fd_hr[%i] == %d\t%s"RST"\n", i, mini_sh->exec->fd_hr[i], tmp->next->word);
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

	exec_signal(2);
	while (1)
	{
		input = readline("&>");
		if (!input)
		{
			printf("minishell: warning: here-document delimited");
			printf(" by end-of-file (wanted '%s')\n", tmp->next->word);
			break ;
		}
		if (ft_strncmp(input, tmp->next->word, ft_strlen(tmp->next->word)) == 0)
		{
			free(input);
			break ;
		}
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
		free_all(mini_sh);
		exit (0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		//g_exit_stt = 130;
		waitpid(child, &g_exit_stt, 0);
		if (WIFEXITED(g_exit_stt))
		{
			g_exit_stt = WEXITSTATUS(g_exit_stt);
		}
		exec_signal(1);
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
	if (mini_sh->sep_type[i_exec + 1] == REDIR_L)
		mini_sh->exec->fd_out = 1;
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
	else
	{
		close(mini_sh->exec->tab_fd[i_exec][1]);
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

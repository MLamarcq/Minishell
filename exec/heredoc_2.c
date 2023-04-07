#include "../ft_minishell.h"


int	init_hr_dc_tab(t_mini_sh *mini_sh)
{
	int i;
	t_parse *tmp;

	tmp = mini_sh->rl_out_head;
	i = 0;
	// if (mini_sh->exec->nbr_fd_r == 0)
	// 	return (FAIL);
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
				//analyse_redir_before_alloc(mini_sh, tmp);
				mini_sh->exec->hr_name[i] = ft_strjoin_rfree(".heredoc", ft_itoa(i));
				mini_sh->exec->fd_hr[i] = open(mini_sh->exec->hr_name[i], O_CREAT | O_RDWR, 0777);
				printf(GREEN"fd_hr[%i] == %d\t%s"RST"\n", i, mini_sh->exec->fd_hr[i], tmp->next->word);
				if (mini_sh->exec->fd_hr[i] == -1)
					return (FAIL);
				tmp = tmp->next;
				// if (mini_sh->exec->ana_r == 0)
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
	char *input;
	//int	i_close;

	while (1)
	{
		input = readline("&>");
		if (ft_strncmp(input, tmp->next->word, ft_strlen(tmp->next->word)) == 0)
		{
			printf("word = %s\n", tmp->next->word);
			printf("input = %s\n", input);
			// i_close = 0;
			// while (mini_sh->exec->tab_fd[i_close])
			// {
			// 	close(mini_sh->exec->tab_fd[i_close][0]);
			// 	close(mini_sh->exec->tab_fd[i_close][1]);
			// 	i_close++;
			// }
			//exit(1);
			break ;
		}
		ft_putstr_fd(input, mini_sh->exec->fd_hr[i]);
	}
}


int	exec_all_hr_doc(t_mini_sh *mini_sh)
{
	int i;
	t_parse *tmp;

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
	if (mini_sh->sep_2 != 0)
	{
		close(mini_sh->exec->tab_fd[i_exec][0]);
		close(mini_sh->exec->tab_fd[i_exec][1]);
	}
	// printf("fd->app = %d\n", mini_sh->exec->fd_app[mini_sh->exec->check_app]);
	printf(RED"i_exec inside app = %d"RST"\n", i_exec);
	// if (mini_sh->sep_2 != 0)
	// {
	// 	close(mini_sh->exec->tab_fd[i_exec][1]);
	// 	close(mini_sh->exec->tab_fd[i_exec][0]);
	// }
	// fprintf(stderr, GREEN"&%s"RST"\n", mini_sh->prepare_exec[i_exec][0]);
	// if (mini_sh->sep_type[i_exec - 1] && mini_sh->sep_type[i_exec - 1] == APPEND)
	// {
	// 	printf(RED"salut"RST"\n");
	// 	mini_sh->exec->fd_in = 0;
	// }
	printf(BOLD_GREEN"mini_sh->exec->check_hr = %d"RST"\n", mini_sh->exec->check_hr);
	mini_sh->exec->fd_in = mini_sh->exec->fd_hr[mini_sh->exec->check_hr];
	//mini_sh->exec->fd_out = 1;
}

void	unlink_hr_dc(t_mini_sh *mini_sh)
{
	int i;

	i = 0;
	while (i < mini_sh->exec->nbr_fd_hr)
	{
		unlink(mini_sh->exec->hr_name[i]);
		i++;
	}
}
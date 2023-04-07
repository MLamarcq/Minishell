#include "../ft_minishell.h"

// int	opening_append_file(t_mini_sh *mini_sh, int i_init_fd)
// {
// 	if (mini_sh->len_prepare_exec == 1)
// 	{
// 		*mini_sh->exec->fd_app = open(mini_sh->prepare_exec[i_init_fd][0], O_CREAT | O_APPEND  | O_RDWR, 0644);
// 		if (!*mini_sh->exec->fd_app)
// 			return (printf("Failure during opening redir_r file\n"), FAIL);
// 	}
// 	else
// 	{
// 		if (mini_sh->sep_type[i_init_fd + 1] && mini_sh->sep_type[i_init_fd] 
// 		== PIPE)
// 		{
// 			*mini_sh->exec->fd_app = open(mini_sh->prepare_exec[i_init_fd + 1][0], O_CREAT | O_APPEND  | O_RDWR, 0644);
// 			if (!*mini_sh->exec->fd_app)
// 				return (printf("Failure during opening redir_r file\n"), FAIL);
// 		}
// 		else
// 		{
// 			*mini_sh->exec->fd_app = open(mini_sh->prepare_exec[i_init_fd + 1][0], O_CREAT | O_APPEND | O_RDWR, 0644);
// 			if (*mini_sh->exec->fd_app == FAIL)
// 				return (printf("Failure during opening redir_r file\n"), FAIL);
// 		}
// 	}
// 	return (SUCCESS);
// }

// int if_append(t_mini_sh *mini_sh, int i_init_fd)
// {
// 	if (mini_sh->sep_type[i_init_fd] == APPEND)
// 	{
// 		if (opening_append_file(mini_sh, i_init_fd) == FAIL)
// 			return (FAIL);
// 	}
// 	else if (mini_sh->sep_type[i_init_fd] == PIPE && mini_sh->sep_type[i_init_fd + 1] == APPEND)
// 	{
// 		if (opening_append_file(mini_sh, i_init_fd) == FAIL)
// 			return (FAIL);
// 	}
// 	return (SUCCESS);
// }

// int if_redir(t_mini_sh *mini_sh, int i_init_fd)
// {
// 	// if (mini_sh->sep_type[i_init_fd] == REDIR_R)
// 		if_redir_r(mini_sh, i_init_fd);
// 	// if (mini_sh->sep_type[i_init_fd] == APPEND)
// 		if_append(mini_sh, i_init_fd);
// 	return (SUCCESS);
// }


void	analyse_append_before_alloc(t_mini_sh *mini_sh, t_parse *tmp)
{
	t_parse *temp;

	temp = tmp;
	if (temp->type == APPEND)
	{
		temp = temp->next;
		printf("temp->word 1 = %s\n", temp->word);
		while (temp)
		{
			//printf("temp->word = %s\n", temp->word);
			if (temp->type == APPEND || temp->type == REDIR_R)
			{
				printf(RED"ici"RST"\n");
				mini_sh->exec->ana_app = 1;
				break ;
			}
			else if (temp->type == PIPE)
			{
				printf(RED"la"RST"\n");
				mini_sh->exec->ana_app = 0;
				break;
			}
			temp = temp->next;
		}
	}
}

int	init_append_tab(t_mini_sh *mini_sh)
{
	int i;
	t_parse *tmp;

	tmp = mini_sh->rl_out_head;
	i = 0;
	// if (mini_sh->exec->nbr_fd_app == 0)
	// 	return (FAIL);
	mini_sh->exec->fd_app = malloc(sizeof(int) * mini_sh->exec->nbr_fd_app + 1);
	if (!mini_sh->exec->fd_app)
		return (FAIL_MALLOC);
	mini_sh->exec->fd_app[mini_sh->exec->nbr_fd_app] = 0;
	while (i < mini_sh->exec->nbr_fd_app)
	{
		while (tmp)
		{
			if (tmp->type == APPEND)
			{
				printf("i app = %d\n", i);
				printf("tmp->next->word = %s\n", tmp->next->word);
				analyse_append_before_alloc(mini_sh, tmp);
				mini_sh->exec->fd_app[i] = open(tmp->next->word, O_CREAT | O_APPEND | O_RDWR, 0644);
				printf(GREEN"fd_app[%i] == %d\t%s"RST"\n", i, mini_sh->exec->fd_app[i], tmp->next->word);
				if (mini_sh->exec->fd_app[i] == -1)
					return (FAIL);
				printf(YELLOW"app"RST"\n");
				tmp = tmp->next;
				if (mini_sh->exec->ana_app == 0)
					break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (SUCCESS);
}


void	do_append(t_mini_sh *mini_sh, int i_exec)
{
	if (mini_sh->sep_2 != 0)
		close(mini_sh->exec->tab_fd[i_exec][1]);
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
	printf(BOLD_GREEN"mini_sh->exec->check_app = %d"RST"\n", mini_sh->exec->check_app);
	mini_sh->exec->fd_out = mini_sh->exec->fd_app[mini_sh->exec->check_app];
}
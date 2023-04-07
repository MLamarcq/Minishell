#include "../ft_minishell.h"

void	analyse_redir_before_alloc(t_mini_sh *mini_sh, t_parse *tmp)
{
	t_parse *temp;

	temp = tmp;
	if (temp->type == REDIR_R)
	{
		temp = temp->next;
		//printf("temp->word 1 = %s\n", temp->word);
		while (temp)
		{
			//printf("temp->word = %s\n", temp->word);
			if (temp->type == REDIR_R || temp->type == APPEND)
			{
				printf(RED"ici"RST"\n");
				mini_sh->exec->ana_r = 1;
				break ;
			}
			else if (temp->type == PIPE)
			{
				printf(RED"la"RST"\n");
				mini_sh->exec->ana_r = 0;
				break;
			}
			temp = temp->next;
		}
	}
}

int	init_redir_r_tab(t_mini_sh *mini_sh)
{
	int i;
	t_parse *tmp;

	tmp = mini_sh->rl_out_head;
	i = 0;
	if (mini_sh->exec->nbr_fd_r == 0)
		return (FAIL);
	mini_sh->exec->fd_r = malloc(sizeof(int) * mini_sh->exec->nbr_fd_r + 1);
	if (!mini_sh->exec->fd_r)
		return (FAIL_MALLOC);
	mini_sh->exec->fd_r[mini_sh->exec->nbr_fd_r] = 0;
	while (i < mini_sh->exec->nbr_fd_r)
	{
		while (tmp)
		{
			if (tmp->type == REDIR_R)
			{
				analyse_redir_before_alloc(mini_sh, tmp);
				mini_sh->exec->fd_r[i] = open(tmp->next->word, O_CREAT | O_TRUNC | O_RDWR, 0644);
				printf(GREEN"fd_r[%i] == %d\t%s"RST"\n", i, mini_sh->exec->fd_r[i], tmp->next->word);
				if (mini_sh->exec->fd_r[i] == -1)
					return (FAIL);
				tmp = tmp->next;
				if (mini_sh->exec->ana_r == 0)
					break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (SUCCESS);
}




// int	rdr_r(t_parse *tmp, t_mini_sh *mini_sh)
// {
// 	if (tmp->type == REDIR_R)
// 	{
// 		// printf("salut\n");
// 		// close()
// 		mini_sh->exec->fd_r = open(tmp->next->word, O_CREAT | O_TRUNC| O_RDWR, 0644);
// 		// printf(BOLD_RED"	%s\n"RST"---\n", tmp->next->word);
// 		if (mini_sh->exec->fd_r == FAIL)
// 			return (printf("Failure during opening redir_r file\n"), FAIL);
// 	}
// 	return (SUCCESS);
// }

// int	rdr_app(t_parse *tmp, t_mini_sh *mini_sh)
// {
// 	if (tmp->type == APPEND)
// 	{
// 		*mini_sh->exec->fd_app = open(tmp->next->word, O_CREAT | O_APPEND | O_RDWR, 0644);
// 		if (*mini_sh->exec->fd_app == FAIL)
// 			return (printf("Failure during opening redir_r file\n"), FAIL);
// 	}
// 	return (SUCCESS);
// }

// int	rdr_l(t_parse *tmp, t_mini_sh *mini_sh)
// {
// 	if (tmp->type == REDIR_L)
// 	{
// 		*mini_sh->exec->fd_l = open(tmp->next->word, O_RDONLY, 0644);
// 		if (*mini_sh->exec->fd_l == FAIL)
// 			return (printf("Failure during opening redir_r file\n"), FAIL);
// 	}
// 	return (SUCCESS);
// }

// int	opening_redir_r_file(t_mini_sh *mini_sh, t_parse *tmp, int i_init_fd)
// {
// 	// t_parse *tmp;

// 	tmp = mini_sh->rl_out_head;
// 	while (tmp)
// 	{
// 		// printf(BOLD_RED"	%s\n"RST"---\n", tmp->word);
// 		// if (rdr_r(tmp, mini_sh) == FAIL)
// 		// 	return (FAIL);
// 		// if (rdr_app(tmp, mini_sh) == FAIL)
// 		// 	return (FAIL);
// 		// if (rdr_l(tmp, mini_sh) == FAIL)
// 		// 	return (FAIL);
// 		//rdr_r(tmp, mini_sh);
// 		rdr_app(tmp, mini_sh);
// 		rdr_l(tmp, mini_sh);
// 		tmp = tmp->next;
// 	}
// 	(void)i_init_fd;
// 	return (SUCCESS);
// }


// int if_redir_r(t_mini_sh *mini_sh, int i_init_fd)
// {
// 	printf("here\n");
// 	if (mini_sh->sep_type[i_init_fd] == REDIR_R)
// 	{
// 		if (opening_redir_r_file(mini_sh) == FAIL)
// 			return (FAIL);
// 	}
// 	else if (mini_sh->sep_type[i_init_fd] == PIPE && mini_sh->sep_type[i_init_fd + 1] == REDIR_R)
// 	{
// 		printf(RED"ici\n"RST);
// 		if (opening_redir_r_file(mini_sh) == FAIL)
// 			return (FAIL);
// 	}
// 	return (SUCCESS);
// }

void	do_redir_r(t_mini_sh *mini_sh, int i_exec)
{
	printf(RED"i_exec inside redir = %d"RST"\n", i_exec);
	if (mini_sh->sep_2 != 0)
	{
		close(mini_sh->exec->tab_fd[i_exec][1]);
		close(mini_sh->exec->tab_fd[i_exec][0]);
	}
	fprintf(stderr, GREEN"%s"RST"\n", mini_sh->prepare_exec[i_exec][0]);
	if (mini_sh->sep_type[i_exec - 1] && mini_sh->sep_type[i_exec - 1] == REDIR_R)
	{
		printf(RED"salut"RST"\n");
		mini_sh->exec->fd_in = 0;
	}
	fprintf(stderr, BOLD_GREEN"%i\t%i"RST"\n", mini_sh->exec->check_r, mini_sh->exec->nbr_fd_r);
	printf(BOLD_GREEN"mini_sh->exec->check_r = %d"RST"\n", mini_sh->exec->check_r);
	mini_sh->exec->fd_out = mini_sh->exec->fd_r[mini_sh->exec->check_r];
	// if (mini_sh->exec->check_r < mini_sh->exec->nbr_fd_r)
	// 	mini_sh->exec->check_r++;
	//fprintf(stderr, BOLD_GREEN"%i\t%i"RST"\n", mini_sh->exec->check_r, mini_sh->exec->nbr_fd_r);
}

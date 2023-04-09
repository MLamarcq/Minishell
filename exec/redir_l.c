#include "../ft_minishell.h"

// int	check_redir_l_error(t_mini_sh *mini_sh)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while(mini_sh->prepare_exec[i])
// 	{
// 		j = 0;
// 		while (mini_sh->prepare_exec[i][j])
// 		{
// 			if (mini_sh->sep_type[i] == REDIR_L)
// 			{
// 				if ((open(mini_sh->prepare_exec[i][j], O_RDONLY) == -1) && opendir(mini_sh->prepare_exec[i][j]) == NULL)
// 				{
// 					printf("minishell: %s: No such file or directory\n", mini_sh->prepare_exec[i][j]);
// 					return (FAIL);
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (SUCCESS);
// }

// int	do_redir_l(t_mini_sh *mini_sh, int i_exec)
// {
// 	// if (check_redir_l_error(mini_sh) == FAIL)
// 	// 	return (FAIL);
// 	if (mini_sh->sep_type[i_exec - 1] && mini_sh->sep_type[i_exec - 1] == REDIR_L)
// 	{
// 		printf("salut\n");
// 		printf("%d\n", i_exec);
// 		*mini_sh->exec->fd_l = open(mini_sh->prepare_exec[i_exec][0], O_RDONLY);
// 		printf(GREEN"word = %s"RST"\n", mini_sh->prepare_exec[i_exec][0]);
// 		if (*mini_sh->exec->fd_l == -1)
// 			return (FAIL);
// 		close(mini_sh->exec->tab_fd[i_exec][0]);
// 		mini_sh->exec->fd_in = *mini_sh->exec->fd_l;
// 	}
// 	return (SUCCESS);
// }

int	init_redir_l_tab(t_mini_sh *mini_sh)
{
	int		i;
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	i = 0;
	if (mini_sh->exec->nbr_fd_l == 0)
		return (FAIL);
	mini_sh->exec->fd_l = malloc(sizeof(int) * mini_sh->exec->nbr_fd_l + 1);
	if (!mini_sh->exec->fd_l)
		return (FAIL_MALLOC);
	mini_sh->exec->fd_l[mini_sh->exec->nbr_fd_l] = 0;
	while (i < mini_sh->exec->nbr_fd_l)
	{
		while (tmp)
		{
			if (tmp->type == REDIR_L)
			{
				// analyse_redir_before_alloc(mini_sh, tmp);
				mini_sh->exec->fd_l[i] = open(tmp->next->word, O_RDONLY, 0644);
				printf(GREEN"fd_l[%i] == %d\t%s"RST"\n", i, mini_sh->exec->fd_l[i], tmp->next->word);
				if (mini_sh->exec->fd_l[i] == -1)
					return (printf("something wrong happened\n"), FAIL);
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

void	do_redir_l(t_mini_sh *mini_sh, int i_exec)
{
	printf(RED"i_exec inside redir = %d"RST"\n", i_exec);
	if (mini_sh->sep_2 == 1)
	{
		close(mini_sh->exec->tab_fd[i_exec][1]);
		close(mini_sh->exec->tab_fd[i_exec][0]);
	}
	fprintf(stderr, GREEN"%s"RST"\n", mini_sh->prepare_exec[i_exec][0]);
	// if (mini_sh->sep_type[i_exec - 1] && mini_sh->sep_type[i_exec - 1] == REDIR_R)
	// {
	// 	printf(RED"salut"RST"\n");
	// 	mini_sh->exec->fd_in = 0;
	// }
	fprintf(stderr, BOLD_GREEN"%i\t%i"RST"\n", mini_sh->exec->check_l, mini_sh->exec->nbr_fd_l);
	fprintf(stderr, BOLD_GREEN"mini_sh->exec->check_l = %d"RST"\n", mini_sh->exec->check_l);
	mini_sh->exec->fd_in = mini_sh->exec->fd_l[mini_sh->exec->check_l];
	if (mini_sh->sep_type[i_exec + 1])
	{
		if (mini_sh->sep_type[i_exec + 1] == PIPE)
			mini_sh->exec->fd_out = mini_sh->exec->tab_fd[i_exec + 1][1];
		else if (mini_sh->sep_type[i_exec + 1] == REDIR_R)
			mini_sh->exec->fd_out = mini_sh->exec->fd_r[mini_sh->exec->check_r];
	}
	// if (mini_sh->exec->check_l < mini_sh->exec->nbr_fd_l)
	// 	mini_sh->exec->check_l++;
	//fprintf(stderr, BOLD_GREEN"%i\t%i"RST"\n", mini_sh->exec->check_l, mini_sh->exec->nbr_fd_l);
}





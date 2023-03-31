#include "../ft_minishell.h"


// int	opening_redir_r_file(t_mini_sh *mini_sh, int i_init_fd)
// {
// 	if (mini_sh->len_prepare_exec == 1)
// 	{
// 		mini_sh->exec->fd_r = open(mini_sh->prepare_exec[i_init_fd][0], O_CREAT | O_TRUNC | O_RDWR, 0644);
// 		if (!mini_sh->exec->fd_r)
// 			return (printf("Failure during opening redir_r file\n"), FAIL);
// 	}
// 	else
// 	{
// 		if (mini_sh->sep_type[i_init_fd + 1] && mini_sh->sep_type[i_init_fd] 
// 		== PIPE)
// 		{
// 			mini_sh->exec->fd_r = open(mini_sh->prepare_exec[i_init_fd + 1][0], O_CREAT | O_TRUNC | O_RDWR, 0644);
// 			if (!mini_sh->exec->fd_r)
// 				return (printf("Failure during opening redir_r file\n"), FAIL);
// 		}
// 		else
// 		{
// 			mini_sh->exec->fd_r = open(mini_sh->prepare_exec[i_init_fd + 1][0], O_CREAT | O_TRUNC| O_RDWR, 0644);
// 			if (mini_sh->exec->fd_r == FAIL)
// 				return (printf("Failure during opening redir_r file\n"), FAIL);
// 		}
// 	}
// 	return (SUCCESS);
// }

int	rdr_r(t_parse *tmp, t_mini_sh *mini_sh)
{
	if (tmp->type == REDIR_R)
	{
		printf("salut\n");
		mini_sh->exec->fd_r = open(tmp->next->word, O_CREAT | O_TRUNC| O_RDWR, 0644);
		printf(BOLD_RED"	%s\n"RST"---\n", tmp->next->word);
		if (mini_sh->exec->fd_r == FAIL)
			return (printf("Failure during opening redir_r file\n"), FAIL);
	}
	return (SUCCESS);
}

int	rdr_app(t_parse *tmp, t_mini_sh *mini_sh)
{
	if (tmp->type == APPEND)
	{
		mini_sh->exec->fd_app = open(tmp->next->word, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (mini_sh->exec->fd_app == FAIL)
			return (printf("Failure during opening redir_r file\n"), FAIL);
	}
	return (SUCCESS);
}

int	rdr_l(t_parse *tmp, t_mini_sh *mini_sh)
{
	if (tmp->type == REDIR_L)
	{
		mini_sh->exec->fd_l = open(tmp->next->word, O_RDONLY, 0644);
		if (mini_sh->exec->fd_l == FAIL)
			return (printf("Failure during opening redir_r file\n"), FAIL);
	}
	return (SUCCESS);
}

int	opening_redir_r_file(t_mini_sh *mini_sh)
{
	t_parse *tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		printf(BOLD_RED"	%s\n"RST"---\n", tmp->word);
		if (rdr_r(tmp, mini_sh) == FAIL)
			return (FAIL);
		if (rdr_app(tmp, mini_sh) == FAIL)
			return (FAIL);
		if (rdr_l(tmp, mini_sh) == FAIL)
			return (FAIL);
		tmp = tmp->next;
	}
	return (SUCCESS);
}


int if_redir_r(t_mini_sh *mini_sh, int i_init_fd)
{
	printf("here\n");
	if (mini_sh->sep_type[i_init_fd] == REDIR_R)
	{
		if (opening_redir_r_file(mini_sh) == FAIL)
			return (FAIL);
	}
	else if (mini_sh->sep_type[i_init_fd] == PIPE && mini_sh->sep_type[i_init_fd + 1] == REDIR_R)
	{
		printf(RED"ici\n"RST);
		if (opening_redir_r_file(mini_sh) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

void	do_redir_r(t_mini_sh *mini_sh, int i_exec)
{
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
	mini_sh->exec->fd_out = mini_sh->exec->fd_r;
}

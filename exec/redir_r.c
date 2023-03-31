#include "../ft_minishell.h"


int	opening_redir_r_file(t_mini_sh *mini_sh, int i_init_fd)
{
	if (mini_sh->len_prepare_exec == 1)
	{
		mini_sh->exec->fd_r = open(mini_sh->prepare_exec[i_init_fd][0], O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (!mini_sh->exec->fd_r)
			return (printf("Failure during opening redir_r file\n"), FAIL);
	}
	else
	{
		if (mini_sh->sep_type[i_init_fd + 1] && mini_sh->sep_type[i_init_fd] 
		== PIPE)
		{
			mini_sh->exec->fd_r = open(mini_sh->prepare_exec[i_init_fd + 1][0], O_CREAT | O_TRUNC | O_RDWR, 0644);
			if (!mini_sh->exec->fd_r)
				return (printf("Failure during opening redir_r file\n"), FAIL);
		}
		else
		{
			mini_sh->exec->fd_r = open(mini_sh->prepare_exec[i_init_fd + 1][0], O_CREAT | O_TRUNC| O_RDWR, 0644);
			if (mini_sh->exec->fd_r == FAIL)
				return (printf("Failure during opening redir_r file\n"), FAIL);
		}
	}
	return (SUCCESS);
}

int if_redir(t_mini_sh *mini_sh, int i_init_fd)
{
	if (mini_sh->sep_type[i_init_fd] == REDIR_R)
	{
		if (opening_redir_r_file(mini_sh, i_init_fd) == FAIL)
			return (FAIL);
	}
	else if (mini_sh->sep_type[i_init_fd] == PIPE && mini_sh->sep_type[i_init_fd + 1] == REDIR_R)
	{
		if (opening_redir_r_file(mini_sh, i_init_fd) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

void	do_redir_r(t_mini_sh *mini_sh, int i_exec)
{
	if (mini_sh->sep_2 != 0)
		close(mini_sh->exec->tab_fd[i_exec][1]);
	mini_sh->exec->fd_out = mini_sh->exec->fd_r;
}

#include "../ft_minishell.h"

int	opening_redir_r_file(t_mini_sh *mini_sh, int i_exec)
{
	if (mini_sh->len_prepare_exec == 1 && !mini_sh->prepare_exec[0][1])
	{
		printf(BACK_PURPLE"i_exec = %d"RST"\n", i_exec);
		mini_sh->exec->fd_r = open(mini_sh->prepare_exec[i_exec][0], O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (!mini_sh->exec->fd_r)
			return (printf("Failure during opening redir_r file\n"), FAIL);
	}
	else
	{
		if (mini_sh->sep_type[i_exec - 1] && mini_sh->sep_type[i_exec - 1] \
		== PIPE && i_exec == mini_sh->sep_2)
		{
			mini_sh->exec->fd_r = open(mini_sh->prepare_exec[i_exec][0], O_CREAT | O_TRUNC | O_RDWR, 0644);
			if (!mini_sh->exec->fd_r)
				return (printf("Failure during opening redir_r file\n"), FAIL);
		}
		else
		{
			printf("i_exec = %d\n", i_exec);
			mini_sh->exec->fd_r = open(mini_sh->prepare_exec[i_exec + 1][0], O_CREAT | O_TRUNC| O_RDWR, 0644);
			if (mini_sh->exec->fd_r == FAIL)
				return (printf("Failure during opening redir_r file\n"), FAIL);
		}
	}
	return (SUCCESS);
}

int	do_redir_r(t_mini_sh *mini_sh, int i_exec)
{
	if (mini_sh->sep_type[i_exec] && mini_sh->sep_type[i_exec] == REDIR_R)
	{
		printf(GREEN"la"RST"\n");
		if (opening_redir_r_file(mini_sh, i_exec) == FAIL)
			return (FAIL);
		close(mini_sh->exec->tab_fd[i_exec][1]);
		mini_sh->exec->fd_out = mini_sh->exec->fd_r;
	}
	return (SUCCESS);
}

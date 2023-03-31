#include "../ft_minishell.h"

int	check_redir_l_error(t_mini_sh *mini_sh)
{
	int i;
	int j;

	i = 0;
	while(mini_sh->prepare_exec[i])
	{
		j = 0;
		while (mini_sh->prepare_exec[i][j])
		{
			if (mini_sh->sep_type[i] == REDIR_L)
			{
				if ((open(mini_sh->prepare_exec[i][j], O_RDONLY) == -1) && opendir(mini_sh->prepare_exec[i][j]) == NULL)
				{
					printf("minishell: %s: No such file or directory\n", mini_sh->prepare_exec[i][j]);
					return (FAIL);
				}
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	do_redir_l(t_mini_sh *mini_sh, int i_exec)
{
	// if (check_redir_l_error(mini_sh) == FAIL)
	// 	return (FAIL);
	if (mini_sh->sep_type[i_exec - 1] && mini_sh->sep_type[i_exec - 1] == REDIR_L)
	{
		printf("salut\n");
		printf("%d\n", i_exec);
		mini_sh->exec->fd_l = open(mini_sh->prepare_exec[i_exec][0], O_RDONLY);
		printf(GREEN"word = %s"RST"\n", mini_sh->prepare_exec[i_exec][0]);
		if (mini_sh->exec->fd_l == -1)
			return (FAIL);
		close(mini_sh->exec->tab_fd[i_exec][0]);
		mini_sh->exec->fd_in = mini_sh->exec->fd_l;
	}
	return (SUCCESS);
}

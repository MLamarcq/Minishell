#include "../ft_minishell.h"

int	opening_redir_r_file(t_mini_sh *mini_sh, int i_exec)
{
	//char *cmd_abs_path;
	if (mini_sh->len_prepare_exec == 1 && !mini_sh->prepare_exec[0][1])
	{
		printf(BACK_PURPLE"i_exec = %d"RST"\n", i_exec);
		mini_sh->exec->fd_r = open(mini_sh->prepare_exec[i_exec][0], O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (!mini_sh->exec->fd_r)
			return (printf("Failure during opening redir_r file\n"), FAIL);
	}
	// else if (mini_sh->sep_type[i_exec] == REDIR_R && mini_sh->prepare_exec[i_exec][0])
	// {
	// 	cmd_abs_path = ft_find_path_2(mini_sh, mini_sh->prepare_exec[i_exec][0]);
	// 	printf(BACK_PURPLE"mini_sh->prepare_exec[i_exec][0] = %s"RST"\n", mini_sh->prepare_exec[i_exec][0]);
	// 	if (access(mini_sh->prepare_exec[i_exec][0], X_OK) == -1 && (access(cmd_abs_path, X_OK) == -1))
	// 	{
	// 		printf("Command '%s' not found\n", mini_sh->prepare_exec[i_exec][0]);
	// 		return (FAIL);
	// 	}
	// 	else
	// 	{
	// 		mini_sh->exec->fd_r = open(mini_sh->prepare_exec[i_exec][0], O_CREAT | O_TRUNC | O_RDWR, 0644);
	// 		if (!mini_sh->exec->fd_r)
	// 			return (printf("Failure during opening redir_r file\n"), FAIL);
	// 		// close(mini_sh->exec->tab_fd[i_exec][1]);
	// 		// mini_sh->exec->fd_out = mini_sh->exec->fd_r;
	// 		//execve(mini_sh->prepare_exec[i_exec][1], mini_sh->prepare_exec[i_exec], mini_sh->env);
	// 	}
	// }
	else
	{
		printf(BACK_PURPLE"i_exec = %d"RST"\n", i_exec);
		if (mini_sh->sep_type[i_exec - 1] && mini_sh->sep_type[i_exec - 1] \
		== PIPE && i_exec == mini_sh->sep_2)
		{
			mini_sh->exec->fd_r = open(mini_sh->prepare_exec[i_exec][0], O_CREAT | O_TRUNC | O_RDWR, 0644);
			if (!mini_sh->exec->fd_r)
				return (printf("Failure during opening redir_r file\n"), FAIL);
		}
		else
		{
			mini_sh->exec->fd_r = open(mini_sh->prepare_exec[i_exec + 1][0], O_CREAT | O_TRUNC| O_RDWR, 0644);
			if (mini_sh->exec->fd_r == FAIL)
				return (printf("Failure during opening redir_r file\n"), FAIL);
		}
	}
	return (SUCCESS);
}

int	check_redi_r_error(t_mini_sh *mini_sh, int i_exec)
{
	t_parse	*tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == REDIR_R)
		{
			tmp = tmp->next;
			if (opendir(tmp->word) != NULL)
			{
				printf("minishell: %s: Is a directory\n", tmp->word);
				return (FAIL);
			}
			else if (tmp->type == _FILE || tmp->type == CMD_ABS)
			{
				if (access(tmp->word, W_OK) == -1)
				{
					printf("minishell: %s: permission denied\n", tmp->word);
					return (FAIL);
				}
			}
		}
		tmp = tmp->next;
	}
	(void)i_exec;
	return (SUCCESS);
}

// int	opening_redir_r_file_2(t_mini_sh *mini_sh, int i_exec)
// {
// 	if (opening_redir_r_file(mini_sh, i_exec) == FAIL)
// 		return (FAIL);
// 	if ()
// }


int	do_redir_r(t_mini_sh *mini_sh, int i_exec)
{
	if (check_redi_r_error(mini_sh, i_exec) == FAIL)
		return (FAIL);
	// if (check_error_before_opening(mini_sh) == FAIL)
	// 	return (FAIL);
	if (mini_sh->sep_type[i_exec] && mini_sh->sep_type[i_exec] == REDIR_R)
	{
		if (opening_redir_r_file(mini_sh, i_exec) == FAIL)
			return (FAIL);
		close(mini_sh->exec->tab_fd[i_exec][1]);
		mini_sh->exec->fd_out = mini_sh->exec->fd_r;
	}
	return (SUCCESS);
}

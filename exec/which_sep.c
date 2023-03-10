#include "../ft_minishell.h"

int	init_exec(t_mini_sh *mini_sh)
{
	mini_sh->exec = malloc(sizeof(t_exec_t));
	if (!mini_sh->exec)
		return (FAIL_MALLOC);
	mini_sh->exec->fd_R = 0;
	mini_sh->exec->fd_L = 0;
	mini_sh->exec->fd_HR = 0;
	mini_sh->exec->fd_APP = 0;
	mini_sh->exec->fd[0] = 0;
	mini_sh->exec->fd[1] = 0;
	return (SUCCESS);
}


int	if_redir_R(t_mini_sh *mini_sh)
{
	t_arr_output *tmp;

	tmp = mini_sh->rl_out_head;
	if (init_exec(mini_sh) < 0)
		return (FAIL);
	if (tmp->type == REDIR_R)
	{
		tmp = tmp->next;
		if (opendir(tmp->word) != NULL)
		{
			printf("minishell: %s: Is a directory", tmp->word);
			return (FAIL);
		}
		else if (tmp->type == _FILE || tmp->type == CMD_ABS)
		{
			if (access(tmp->word,W_OK) == -1)
			{
				printf("minishell: %s: permission denied", tmp->word);
				return (FAIL);
			}
			mini_sh->exec->fd_R = open(tmp->word, O_CREAT | O_TRUNC, 0777);
			if (mini_sh->exec->fd_R == -1)
			{
				printf("Failed during opening the file");
				return (FAIL);
			}
		}
		else if (tmp->type == ARG || tmp->type == CMD)
		{
			mini_sh->exec->fd_R = open(tmp->word, O_CREAT | O_TRUNC | 0777);
			if (mini_sh->exec->fd_R == -1)
			{
				printf("Failure during opening the file");
				return (FAIL);
			}
		}
		//close(mini_sh->exec->fd_R);
		// if (tmp->type != ARG)
		// exec->fd = open(tmp->next->word, )
	}
	free(mini_sh->exec);
	return (SUCCESS);
}

int	if_redir_L(t_mini_sh *mini_sh)
{
	t_arr_output *tmp;
	
	tmp = mini_sh->rl_out_head;
	if (init_exec(mini_sh) < 0)
		return (FAIL);
	if (tmp->type == REDIR_L)
	{
		tmp = tmp->next;
		mini_sh->exec->fd_L = open(tmp->word, O_RDONLY, 0777);
		if (!mini_sh->exec->fd_L)
		{
			printf("Failure during opening the file");
			return (FAIL);
		}
	}
	return (SUCCESS);
}
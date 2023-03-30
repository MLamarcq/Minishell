#include "../ft_minishell.h"

int	check_redi_r_error(t_mini_sh *mini_sh)
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
				if (print_error(1, tmp) == FAIL)
					return (FAIL);
			}
			if (tmp->type == _FILE || tmp->type == CMD_ABS)
			{
				if (access(tmp->word, W_OK) == -1)
				{
					if (print_error(2, tmp) == FAIL)
						return (FAIL);
				}
			}
			if (tmp->type == _FILE && (access(tmp->word, W_OK) == 0))
			{
				if (tmp->next && (tmp->next->type != CMD_ABS && tmp->next->type != _FILE && !is_sep(tmp->next->word)))
				{
					if (print_error(3, tmp) == FAIL)
						return (FAIL);
				}
				else if (tmp->next && !is_sep(tmp->next->word))
				{
					if (print_error(4, tmp) == FAIL)
						return (FAIL);
				}
			}

		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}


int print_error(int index, t_parse *tmp)
{
	if (index == 1)
	{
		printf("minishell: %s: Is a directory\n", tmp->word);
		return (FAIL);
	}
	else if (index == 2)
	{
		printf("minishell: %s: permission denied\n", tmp->word);
		return (FAIL);
	}
	else if (index == 3)
	{
		printf("%s: connot access '%s' : No such file or directory\n", \
		tmp->next->word, tmp->next->word);
		return (FAIL);
	}
	else if (index == 4)
	{
		printf("minishell: syntax error near unexpected token '%s'\n", \
		tmp->next->word);
		return (FAIL);
	}
	return (SUCCESS);
}


// int redir_error(t_mini_sh *mini_sh)
// {

// }
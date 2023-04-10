#include "../ft_minishell.h"

int	redir_l_error(t_mini_sh *mini_sh)
{
	t_parse *tmp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == PIPE && tmp->next->type == REDIR_L)
		{
			print_error(4, tmp);
			return (FAIL);
		}
		if (tmp->type == REDIR_L)
		{
			if (opendir(tmp->next->word) != NULL)
			{
				printf("minishell: %s: Is a directory\n", tmp->next->word);
				return (FAIL);
			}
			else if (tmp->next->type != _FILE && tmp->next->type != CMD_ABS)
			{
				printf("minishell: %s: No such file or directory\n", tmp->next->word);
				return (FAIL);
			}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
#include "../ft_minishell.h"

// int	count_sep_2(t_mini_sh *mini_sh)
// {
// 	t_arr_output *tmp;

// 	//printf("C1\n");
// 	tmp = mini_sh->rl_out_head;
// 	mini_sh->flag = 0;
// 	//printf("word = %s\n", tmp->word);
// 	if (is_sep(tmp->word) == SUCCESS)
// 	{	
// 		if (tmp->type == PIPE)
// 		{
// 			printf("minishell: syntac error near unexpected token '|'\n");
// 			return (2);
// 		}
// 		if (!tmp->next)
// 		{
// 			mini_sh->flag = 1;
// 			return (3);
// 		}
// 		mini_sh->flag = 1;
// 		tmp = tmp->next;
// 	}
// 	//printf("word = %s\n", tmp->word);
// 	while (tmp->next != NULL)
// 	{
// 		//printf("C2\n");
// 		if (is_sep(tmp->word) == SUCCESS)
// 			mini_sh->sep_2++;
// 		if (tmp)
// 			tmp = tmp->next;
// 	}
// 	if (is_sep(tmp->word) == SUCCESS)
// 	{
// 		mini_sh->sep_2 = 0;
// 		return (FAIL);
// 	}
// 	printf("res = %d\n", mini_sh->sep_2);
// 	return (SUCCESS);
// }

// int	first_sep_error(t_mini_sh *mini_sh)
// {
// 	t_arr_output *tmp;

// 	tmp = mini_sh->rl_out_head;
// 	if (tmp->type != REDIR_L)
// 	{
// 		if (!tmp->next)
// 		{
// 			printf("minishell: syntax error near unexpected token 'newline'\n");
// 			return (FAIL);
// 		}
// 	}
// 	else if (tmp->type == REDIR_L)
// 	{
// 		if (tmp->next && tmp->next->type != _FILE && tmp->next->type != CMD_ABS)
// 		{
// 			printf("minishell: %s: No such file or directory", tmp->next->word);
// 			return (FAIL);
// 		}
// 		else if (!tmp->next)
// 		{
// 			printf("minishell: syntax error near unexpected token 'newline'\n");
// 			return (FAIL);
// 		}
// 	}
// 	return (SUCCESS);
// }

// int	check_error_first_sep(t_mini_sh *mini_sh)
// {
// 	if (count_sep_2(mini_sh) == FAIL)
// 	{
// 		printf("minishell: syntax error near unexpected token 'newline'\n");
// 		return (FAIL);
// 	}
// 	// else if (count_sep_2(mini_sh) == 2)
// 	// 	return (FAIL);
// 	printf("flag = %d\n", mini_sh->flag);
// 	if (mini_sh->flag == 1)
// 	{
// 		if (first_sep_error(mini_sh) == 2)
// 		{
// 			mini_sh->sep_2 = 0;
// 			return (FAIL);
// 		}
// 		else if (first_sep_error(mini_sh) == FAIL)
// 		{
// 			mini_sh->sep_2 = 0;
// 			return (FAIL);
// 		}
// 	}
// 	return (SUCCESS);
// }

int	check_first_is_sep(t_mini_sh *mini_sh)
{
	t_arr_output *tmp;

	tmp = mini_sh->rl_out_head;
	if (is_sep(tmp->word) == SUCCESS)
	{
		if (tmp->type == PIPE)
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			return (FAIL);
		}
		else if (tmp->type != REDIR_L)
		{
			if (!tmp->next)
			{
				printf("minishell: syntax error near unexpected token 'newline'");
				return (FAIL);
			}
		}
	}
	return (SUCCESS);
}

int	check_first_is_sep_2(t_mini_sh *mini_sh)
{
	t_arr_output *tmp;

	tmp = mini_sh->rl_out_head;
	if (is_sep(tmp->word) == SUCCESS)
	{
		if (tmp->type == REDIR_L)
		{
			if (tmp->next && tmp->next->type != _FILE && tmp->next->type != CMD_ABS)
			{
				printf("minishell: %s: No such file or directory", tmp->next->word);
				return (FAIL);
			}
			if (!tmp->next)
			{
				printf("minishell: syntax error near unexpected token 'newline'\n");
				return (FAIL);
			}
		}
	}
	return (SUCCESS);
}

int	check_first_sep_error_2(t_mini_sh *mini_sh)
{
	if (check_first_is_sep(mini_sh) == FAIL)
		return (FAIL);
	if (check_first_is_sep_2(mini_sh) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	count_sep_2(t_mini_sh *mini_sh)
{
	t_arr_output *tmp;

	tmp = mini_sh->rl_out_head;
	if (check_first_sep_error_2(mini_sh) == FAIL)
		return (FAIL);
	tmp = tmp->next;
	while (tmp->next != NULL)
	{
		if (is_sep(tmp->word) == SUCCESS)
			mini_sh->sep_2++;
		if (tmp)
			tmp = tmp->next;
	}
	if (is_sep(tmp->word) == SUCCESS)
	{
		if (tmp->type == PIPE)
		{
			printf("minishell: syntax error near unexpected token '|'");
			return (FAIL);
		}
		else
		{
			printf("minishell: syntax error near unexpected token 'newline'\n");
			return (FAIL);
		}
	}
	printf("res = %d\n", mini_sh->sep_2);
	return (SUCCESS);
}

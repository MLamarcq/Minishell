#include "../ft_minishell.h"

int	first_is_sep(t_mini_sh *mini_sh)
{
	t_arr_output *tmp;

	tmp = mini_sh->rl_out_head;
	//printf("tmp->inside %s\n", tmp->word);
	// if (tmp->type == PIPE)
	// {
	// 	printf("C2\n");
	// 	printf("bash: syntax error near unexpected token '|'");
	// 	return (2);
	// }
	if (tmp->type == REDIR_L)
	{
		// if (tmp->next && tmp->next->type != _FILE)
		// {
		// 	printf("bash: %s: No such file or directory", tmp->next->word);
		// 	return (FAIL);
		// }
		// else if (!tmp->next)
		// {
		// 	printf("bash: syntax error near unexpected token 'newline'");
		// 	return (FAIL);
		// }
		return (SUCCESS);
	}
	else if(tmp->type == REDIR_R)
	{
		// if (!tmp->next)
		// {
		// 	printf("bash: syntax error near unexpected token 'newline'");
		// 	return (FAIL);
		// }
		return (SUCCESS);
	}
	else if (tmp->type == APPEND || tmp->type == HR_DOC)
	{
		// if (!tmp->next)
		// {
		// 	printf("bash: syntax error near unexpected token 'newline'");
		// 	return (FAIL);
		// }
		return (SUCCESS);
	}
	return (FAIL);
}

int	check_first_sep_error(t_mini_sh *mini_sh)
{
	t_arr_output *tmp;

	tmp = mini_sh->rl_out_head;

	// printf("%i\n", CMD);
	// printf("%i\n", CMD_ABS);
	// printf("%i\n", PIPE);
	// printf("%i\n", ARG);
	// printf("%i\n", OPTION);
	// printf("%i\n", REDIR_L);
	// printf("%i\n", REDIR_R);
	// printf("%i\n", _FILE);
	// printf("%i\n", APPEND);
	// printf("%i\n", HR_DOC);
	if (first_is_sep(mini_sh) == SUCCESS && tmp->type != REDIR_L)
	{
		if (!tmp->next)
		{
			printf("bash: syntax error near unexpected token 'newline'");
			return (FAIL);
		}
		return (SUCCESS);
	}
	else if (first_is_sep(mini_sh) == SUCCESS && tmp->type == REDIR_L)
	{
		// && check if there is absolut path : begin with /
		if (tmp->next && tmp->next->type != _FILE && tmp->next->type != CMD_ABS)
		{
			printf("bash: %s: No such file or directory", tmp->next->word);
			return (FAIL);
		}
		else if (!tmp->next)
		{
			printf("bash: syntax error near unexpected token 'newline'");
			return (FAIL);
		}
		return (SUCCESS);
	}
	// else if (first_is_sep(mini_sh) == 2)
	// 	return (FAIL);
	return (2);
}

int	is_last_sep(t_mini_sh *mini_sh)
{
	t_arr_output *tmp;

	tmp = mini_sh->rl_out_head;
	if (tmp->type == PIPE)
		return (2);
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->type == PIPE && !tmp->next)
		return (2);
	else if (tmp->type == REDIR_L)
	{
		if (!tmp->next)
			return (FAIL);
	}
	else if (tmp->type == REDIR_R)
	{
		if (!tmp->next)
			return (FAIL);
	}
	else if (tmp->type == APPEND || tmp->type == HR_DOC)
		if (!tmp->next)
			return (FAIL);
	return (SUCCESS); 
}

int	check_last_sep_error(t_mini_sh *mini_sh)
{
	if (is_last_sep(mini_sh) == FAIL)
	{
		printf("bash: syntax error near unexpected token 'newline'");
		return (FAIL);
	}
	else if (is_last_sep(mini_sh) == 2)
	{
		printf("bash: syntax error near unexpected token '|'");
		return (FAIL);
	}
	return (SUCCESS);
}

int	count_sep(t_mini_sh *mini_sh)
{
	t_arr_output *tmp;

	tmp = mini_sh->rl_out_head;
	//printf("res 10 = %d\n", check_first_sep_error(mini_sh));
	if (check_first_sep_error(mini_sh) == FAIL)
		return (FAIL);
	else if (check_first_sep_error(mini_sh) == SUCCESS)
		mini_sh->sep = mini_sh->sep - 1;
	else if (check_last_sep_error(mini_sh) == FAIL)
		return (FAIL);
	while (tmp)
	{
	//	printf("tmp = %s\n", tmp->word);
		if (ft_strncmp(tmp->word, "|", ft_strlen(tmp->word)) == 0)
			mini_sh->sep++;
		else if (ft_strncmp(tmp->word, ">", ft_strlen(tmp->word)) == 0)
			mini_sh->sep++;
		else if (ft_strncmp(tmp->word, "<", ft_strlen(tmp->word)) == 0)
			mini_sh->sep++;
		else if (ft_strncmp(tmp->word, ">>", ft_strlen(tmp->word)) == 0)
			mini_sh->sep++;
		else if (ft_strncmp(tmp->word, "<<", ft_strlen(tmp->word)) == 0)
			mini_sh->sep++;
		//printf("res1 = %d\n", mini_sh->sep);
		tmp = tmp->next;
	}
	//printf("res 10 = %d\n", check_first_sep_error(mini_sh));
	// if (check_first_sep_error(mini_sh) == SUCCESS)
	// 	mini_sh->sep = mini_sh->sep - 1;
	//printf("res = %d\n", mini_sh->sep);
	return (SUCCESS);
}
// int	count_sep(t_mini_sh *mini_sh)
// {

// }
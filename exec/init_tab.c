#include "../ft_minishell.h"

int	is_sep(char *word)
{
	//printf("here\n");
	if (ft_strncmp(word, "|", ft_strlen(word)) == 0)
	{
		//printf("c1\n");
		return (SUCCESS);
	}
	else if (ft_strncmp(word, ">", ft_strlen(word)) == 0)
	{
		//printf("c2\n");
		return (SUCCESS);
	}
	else if (ft_strncmp(word, "<", ft_strlen(word)) == 0)
	{
		//printf("c3\n");
		return (SUCCESS);
	}
	else if (ft_strncmp(word, ">>", ft_strlen(word)) == 0)
	{
		//printf("c4\n");
		return (SUCCESS);
	}
	else if (ft_strncmp(word, "<<", ft_strlen(word)) == 0)
	{
		//printf("c5\n");
		return (SUCCESS);
	}
	return (FAIL);
}

int	count_word_for_alloc(t_mini_sh *mini_sh, t_arr_output *rlout)
{
	t_arr_output *tmp;

	tmp = rlout;
	if (!tmp)
		return (FAIL);
	while (tmp)
	{
		//printf("word = %s\n", tmp->word);
		//printf("nbr_word = %d\n", mini_sh->nbr_word);
		if (is_sep(tmp->word) == SUCCESS)
		{
			//printf("word in = %s\n", tmp->word);
			return (SUCCESS);
		}
		mini_sh->nbr_word++;
		//printf("nbr_word = %d\n", mini_sh->nbr_word);
		if (tmp)
			tmp = tmp->next;
	}
	//printf("nbr_word = %d\n", mini_sh->nbr_word);
	return (SUCCESS);
}

int	init_tab(t_mini_sh *mini_sh)
{
	int i;
	int j;
	int len = 0;
	t_arr_output *tmp;

	tmp = mini_sh->rl_out_head;
	if (count_sep(mini_sh) == FAIL)
		return (FAIL);
	printf("nb sep = %d\n", mini_sh->sep);
	mini_sh->prep_exec = (char ***)malloc(sizeof(char **) * (mini_sh->sep + 1));
	if (!mini_sh->prep_exec)
		return (FAIL_MALLOC);
	mini_sh->prep_exec[mini_sh->sep] = NULL;

	i = 0;
	while (tmp)
	{
		//printf("word = %s\n", tmp->word);
		if (count_word_for_alloc(mini_sh, tmp) == FAIL)
			return (FAIL);
		printf("len = %d\n", mini_sh->nbr_word);
		mini_sh->prep_exec[i] = (char **)malloc(sizeof(char *) * (mini_sh->nbr_word + 1));
		if (!mini_sh->prep_exec[i])
			return (FAIL_MALLOC);
		mini_sh->nbr_word = 0;
		j = 0;
		while (is_sep(tmp->word) == FAIL)
		{
			//printf("here\n");
			mini_sh->prep_exec[i][j] = ft_strdup(tmp->word);
			printf("mini_sh->prep_exec[%i][%i] = %s\n", i, j, mini_sh->prep_exec[i][j]);
			len = 0;
			while (mini_sh->prep_exec[len])
				len++;
			printf(RED"-> len %i\n\n"RST, len);

			j++;
			tmp = tmp->next;
			if (!tmp)
				break ;
		}
		mini_sh->prep_exec[i][j] = 0;
		printf("-----------------------------------------------------------\n");
		i++;
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
	printf("i: %i\n", i);
	(void)tmp;
	return (SUCCESS);
}

int	if_empty_chain(t_mini_sh *mini_sh)
{
	int	val_init_tab;

	val_init_tab = init_tab(mini_sh);
	if (val_init_tab == FAIL || val_init_tab == FAIL_MALLOC)
		return (FAIL);

	int i;
	int j;
	// int len = 0;

	// while (mini_sh->prep_exec[len])
	// 	len++;
	// printf("-> len %i\n\n", len);
	i = 0;

	// y a pa de segfault
	while (mini_sh->prep_exec[i] && mini_sh->prep_exec[i][j])
	{
		j = 0;
		printf("\n");
		//len = 0;
		//printf("big : %s\n", mini_sh->prep_exec[i]);
		while (mini_sh->prep_exec[i][j])
		{
			printf("word[%d][%d] = %s\n", i, j, mini_sh->prep_exec[i][j]);
			printf("i: %i\n", i);
			j++;
		}
		printf("C1\n");
		//printf("len = %d\n", mini_sh->nbr_word);
		i++;
	}
	printf("C2\n");
	return (SUCCESS);
}
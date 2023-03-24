#include "../ft_minishell.h"

// int	there_is_a_heredoc(t_mini_sh *mini_sh, int i)
// {
// 	while (mini_sh->sep_type[i])
// 	{
// 		if (ft_strncmp("<<", mini_sh->prepare_exec[i][j], ft_strlen(mini_sh->prepare_exec[i][j])) == 0)
// 		{
// 			if (j == 0)
// 				return (1);
// 			else if (j == 1)
// 				return (2);
// 			else if (j > 1)
// 				return (3);
// 			else if (j > 2)
// 				return (FAIL);
// 		}
// 		j++;
// 	}
// 	return (FAIL);
// }

// int	witch_heredoc(t_mini_sh *mini_sh, int i)
// {
// 	int j;

// 	j = 0;
// 	if (there_is_a_heredoc(mini_sh, i) == FAIL)
// 		return (FAIL);
// 	else if (there_is_a_heredoc(mini_sh, i) == 1)
// 		do_simple_heredoc(mini_sh, i);
// 	// else if (there_is_a_heredoc(mini_sh, i) == 2)
// 	// 	do_heredoc_cmd(mini_sh);
// 	// else if (there_is_a_heredoc(mini_sh, i) == 3)
// 	// 	do_heredoc_big_cmd(mini_sh);
// 	return (SUCCESS);
// }

// int	do_simple_heredoc(t_mini_sh *mini_sh, int i)
// {
// 	char *input;


// 	while (1)
// 	{
// 		input = readline(">");

// 	}
// }

int	init_heredoc(t_mini_sh *mini_sh)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (mini_sh->sep_type[i])
	{
		if (mini_sh->sep_type[i] == HR_DOC)
			j++;
		i++;
	}
	printf(RED"j = %d"RST"\n", j);
	mini_sh->hr_doc_tab = (int *)malloc(sizeof(int) * j + 1);
	if (!mini_sh->hr_doc_tab)
		return (FAIL_MALLOC);
	mini_sh->hr_doc_tab[j] = 0;
	i = 0;
	while (j > 0)
	{
		mini_sh->file_heredoc = ft_strjoin_rfree(".heredoc", ft_itoa(i));
		mini_sh->hr_doc_tab[i] = open(mini_sh->file_heredoc, O_CREAT | O_RDWR, 0777);
		printf(BACK_BLUE"hr_doc = %d"RST"\n", mini_sh->hr_doc_tab[i]);
		if (!mini_sh->hr_doc_tab[i])
			return (FAIL_MALLOC);
		i++;
		j--;
	}
	return (SUCCESS);
}

int	there_is_a_heredoc(t_mini_sh *mini_sh, int i_exec)
{
	if (init_heredoc(mini_sh) != 1)
		return (FAIL);
	else
	{
		//if_hr_doc(mini_sh);
		if (i_exec == 0 || mini_sh->sep_type[i_exec - 1] == PIPE)
			do_simple_heredoc(mini_sh, i_exec);
	}
	return (SUCCESS);
}


//quand seulement heredoc
int	do_simple_heredoc(t_mini_sh *mini_sh, int i_exec)
{
	int i_close;
	char *input;

	//printf("hehe\n");
	while (1)
	{
		dup2(0, 0);
		dup2(1, 1);
		input = readline("&>");

		// close(mini_sh->exec->tab_fd[i_exec][0]);
		if (ft_strncmp(input, mini_sh->prepare_exec[i_exec][0], ft_strlen(mini_sh->prepare_exec[i_exec][0])) == 0)
		{
			i_close = 0;
			while (mini_sh->exec->tab_fd[i_close])
			{
				close(mini_sh->exec->tab_fd[i_close][0]);
				close(mini_sh->exec->tab_fd[i_close][1]);
				i_close++;
			}
			exit(1);
			break ;
			//fprintf(stderr, "break\n");
		}
		//dup2(mini_sh->hr_doc_tab[i_exec], 1);
		//printf("%s\n", input);
		ft_putstr_fd(input, mini_sh->hr_doc_tab[0]);
	}
	unlink(mini_sh->file_heredoc);
	free(mini_sh->file_heredoc);
	return (SUCCESS);
}

// int	heredoc_cmd(t_mini_sh *mini_sh)
// {

// }
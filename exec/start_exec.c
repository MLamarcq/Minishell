/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:33:14 by mael              #+#    #+#             */
/*   Updated: 2023/03/15 23:38:59 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../ft_minishell.h"

// int	init_sep_type(t_mini_sh *mini_sh)
// {
// 	t_parse *tmp;
// 	int i;
// 
// 	tmp = mini_sh->rl_out_head;
// 	printf("nbr sep = %d\n", mini_sh->sep_2);
// 	mini_sh->sep_type = (int*)malloc(sizeof(int) * mini_sh->sep_2 + 1);
// 	if (!mini_sh->sep_type)
// 		return (FAIL_MALLOC);
// 	printf("\n.......................\n\n");
// 	i = 0;
// 	while (tmp)
// 	{
// 		if (is_sep(tmp->word) == SUCCESS)
// 		{
// 			printf("type = %d\n", tmp->type);
// 			mini_sh->sep_type[i] = tmp->type;
// 			printf("sep_type[%i] = %d\n", i, mini_sh->sep_type[i]);
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// 	mini_sh->sep_type[i] = 0;
// 	printf("\n.......................\n\n");
// 	i = 0;
// 	while (mini_sh->sep_type[i])
// 	{
// 		if (mini_sh->sep_type[i] == PIPE)
// 			printf("PIPE\n");
// 		else if (mini_sh->sep_type[i] == REDIR_L)
// 			printf("REDIR_L\n");
// 		else if (mini_sh->sep_type[i] == REDIR_R)
// 			printf("REDIR_R\n");
// 		else if (mini_sh->sep_type[i] == APPEND)
// 			printf("APPEND\n");
// 		else if (mini_sh->sep_type[i] == HR_DOC)
// 			printf("HR_DOC\n");
// 		else
// 			printf("other type = %d\n", mini_sh->sep_type[i]);
// 		i++;
// 	}
// 	printf("\ni = %d\n", i);
// 	return (SUCCESS);
// }

// int	child_process(char **cmds_to_exec)
// {
// 
// 	// builtin
// 	// redirections
// 	return (SUCCESS);
// }

// int	is_all_pids_full(t_mini_sh *mini_sh)
// {
// 	int	i;
// 
// 	i = 0;
// 	while (mini_sh->pids[i])
// 	{
// 		if (mini_sh->pids[i] == 0)
// 			return (FAIL);
// 	}
// 	return (SUCCESS);
// }

// int	start_exec(t_mini_sh *mini_sh)
// {
// 	int i;
// 
// 	mini_sh->pids = (pid_t *)malloc((sizeof (pid_t)) * (mini_sh->sep_2 + 2));
// 	if (!mini_sh->pids)
// 		return (FAIL_MALLOC);
// 	while (mini_sh->prepare_exec[i])
// 	{
// 		mini_sh->pids[i] = fork();
// 		if (mini_sh->pids[i] == -1)
// 			return (FAIL)
// 		if (mini_sh->pids[i] == 0)
// 			child_process(mini_sh->prepare_exec[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (mini_sh->pids[i])
// 	{
// 		waitpid(mini_sh->pids[i], NULL, 0);
// 	}
// 	// function while tous est 0
// 	// 
// }

// char ** -> {PIPE, PIPE, REDIR_R, PIPE}

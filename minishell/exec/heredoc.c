/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:53:46 by ggosse            #+#    #+#             */
/*   Updated: 2023/05/02 08:12:32 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	init_tab_hrdoc(t_mini_sh *mini_sh, int j)
{
	mini_sh->hr_doc_tab = (int *)malloc(sizeof(int) * j + 1);
	if (!mini_sh->hr_doc_tab)
		return (FAIL_MALLOC);
	return (SUCCESS);
}

int	init_heredoc(t_mini_sh *mini_sh)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (mini_sh->sep_type[++i])
	{
		if (mini_sh->sep_type[i] == HR_DOC)
			j++;
	}
	if (init_tab_hrdoc(mini_sh, j) == FAIL_MALLOC)
		return (FAIL_MALLOC);
	mini_sh->hr_doc_tab[j] = 0;
	i = 0;
	while (j > 0)
	{
		mini_sh->file_heredoc = ft_strjoin_rfree(".heredoc", ft_itoa(i));
		mini_sh->hr_doc_tab[i] = open(mini_sh->file_heredoc, \
		O_CREAT | O_RDWR, 0777);
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
		if (i_exec == 0 || mini_sh->sep_type[i_exec - 1] == PIPE)
			do_simple_heredoc(mini_sh, i_exec);
	}
	return (SUCCESS);
}

int	do_simple_heredoc(t_mini_sh *mini_sh, int i_exec)
{
	int		i_close;
	char	*input;

	while (1)
	{
		dup2(0, 0);
		dup2(1, 1);
		input = readline(">");
		if (ft_strncmp(input, mini_sh->prepare_exec[i_exec][0], \
		ft_strlen(mini_sh->prepare_exec[i_exec][0])) == 0)
		{
			i_close = 0;
			while (mini_sh->exec->tab_fd[i_close])
			{
				close(mini_sh->exec->tab_fd[i_close][0]);
				close(mini_sh->exec->tab_fd[i_close][1]);
				i_close++;
			}
			exit(1);
		}
		ft_putstr_fd(input, mini_sh->hr_doc_tab[0]);
	}
	unlink(mini_sh->file_heredoc);
	free(mini_sh->file_heredoc);
	return (SUCCESS);
}

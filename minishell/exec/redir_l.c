/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:56:38 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/26 17:02:56 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	analyse_redir_before_alloc_2(t_mini_sh *mini_sh, t_parse *tmp)
{
	t_parse	*temp;

	temp = tmp;
	if (temp->type == REDIR_L)
	{
		temp = temp->next;
		while (temp)
		{
			if (temp->type == REDIR_L)
			{
				mini_sh->exec->ana_l = 1;
				break ;
			}
			else if (temp->type == PIPE)
			{
				mini_sh->exec->ana_l = 0;
				break ;
			}
			temp = temp->next;
		}
	}
}

void	change_nbr_l(t_mini_sh *mini_sh)
{
	int		check;
	t_parse	*tmp;
	t_parse	*temp;

	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		check = 0;
		if (tmp->type == REDIR_L)
		{
			temp = tmp->next;
			while (temp)
			{
				if (is_sep(temp->word) == SUCCESS)
				{
					if (temp->type == REDIR_L)
						check = 1;
					if (check == 1)
						mini_sh->exec->nbr_fd_l = mini_sh->exec->nbr_fd_l - 1;
					break ;
				}
				temp = temp->next;
			}
		}
		tmp = tmp->next;
	}
}

int	init_redir_l_tab(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	int		i;

	tmp = mini_sh->rl_out_head;
	i = -1;
	if (mini_sh->exec->nbr_fd_l == 0)
		return (FAIL);
	change_nbr_l(mini_sh);
	mini_sh->exec->fd_l = malloc(sizeof(int) * mini_sh->exec->nbr_fd_l + 1);
	if (!mini_sh->exec->fd_l)
		return (FAIL_MALLOC);
	while (++i < mini_sh->exec->nbr_fd_l)
		mini_sh->exec->fd_l[i] = FAIL;
	i = -1;
	while (++i < mini_sh->exec->nbr_fd_l)
	{
		while (tmp)
		{
			if (tmp->type == REDIR_L)
			{
				analyse_redir_before_alloc_2(mini_sh, tmp);
				if (mini_sh->exec->fd_l[i] != FAIL)
					close(mini_sh->exec->fd_l[i]);
				mini_sh->exec->fd_l[i] = open(tmp->next->word, O_RDONLY, 0644);
				if (mini_sh->exec->fd_l[i] == -1)
					return (printf("something wrong happened\n"), FAIL);
				printf(GREEN"fd_l[%i] == %d\t%s"RST"\n", i, mini_sh->exec->fd_l[i], tmp->next->word);
				tmp = tmp->next;
				if (mini_sh->exec->ana_l == 0)
					break ;
			}
			tmp = tmp->next;
		}
	}
	return (SUCCESS);
}

void	do_good_redir(t_mini_sh *mini_sh, int i_exec)
{
	// t_parse	*tmp;
	// t_parse	*temp;
	int i;
	
	// tmp = mini_sh->rl_out_head;
	i = i_exec;
	while (mini_sh->sep_type && mini_sh->sep_type[i] != FAIL && (mini_sh->sep_type[i] != PIPE && mini_sh->sep_type[i] != REDIR_R && mini_sh->sep_type[i] != APPEND))
	{
		//printf(PURPLE"sep = %d\n"RST, mini_sh->sep_type[i]);
		i++;
	}
	if (mini_sh->sep_type[i] == PIPE)
		mini_sh->exec->fd_out = mini_sh->exec->tab_fd[i][1];
	else if (mini_sh->sep_type[i] == REDIR_R)
		mini_sh->exec->fd_out = mini_sh->exec->fd_r[mini_sh->exec->check_r];
	else if (mini_sh->sep_type[i] == APPEND)
		mini_sh->exec->fd_out = \
		mini_sh->exec->fd_app[mini_sh->exec->check_app];
}

int	do_good_redir_l(t_mini_sh *mini_sh, int i_exec)
{
	// // t_parse	*tmp;
	// // t_parse	*temp;
	int i;
	
	// // tmp = mini_sh->rl_out_head;
	i = i_exec;
	// while (mini_sh->sep_type[i] != FAIL && (mini_sh->sep_type[i] != PIPE && mini_sh->sep_type[i] != REDIR_R && mini_sh->sep_type[i] != APPEND))
	// {
	// 	//printf(PURPLE"sep = %d\n"RST, mini_sh->sep_type[i]);
	// 	i++;
	// }
	// if (mini_sh->sep_type[i] == PIPE)
	// 	mini_sh->exec->fd_out = mini_sh->exec->tab_fd[i][1];
	// else if (mini_sh->sep_type[i] == REDIR_R)
	// 	mini_sh->exec->fd_out = mini_sh->exec->fd_r[mini_sh->exec->check_r];
	// else if (mini_sh->sep_type[i] == APPEND)
	// 	mini_sh->exec->fd_out = 
	// 	mini_sh->exec->fd_app[mini_sh->exec->check_app];
	while (mini_sh->sep_type && mini_sh->sep_type[i] && i < mini_sh->sep_2)
	{
		if (mini_sh->sep_type[i] != REDIR_L && mini_sh->sep_type[i] != HR_DOC)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}


void	do_redir_l(t_mini_sh *mini_sh, int i_exec)
{
	if (mini_sh->sep_2 == 1)
		close(mini_sh->exec->tab_fd[i_exec][1]);
	mini_sh->exec->fd_in = mini_sh->exec->fd_l[mini_sh->exec->check_l];
	if (mini_sh->sep_type && do_good_redir_l(mini_sh, i_exec) == SUCCESS)// mini_sh->sep_type[i_exec + 2] == FAIL)
	{
		printf(BACK_RED"start"RST"\n");
		// printf(BACK_CYAN"mini_sh->sep_type[i_exec + 1]: %i"RST"\n", mini_sh->sep_type[i_exec + 1]);
		// print_type(mini_sh->sep_type[i_exec + 1]);
		mini_sh->exec->fd_out = 1;
	}
	else if (mini_sh->sep_type[i_exec + 1] && mini_sh->sep_type[i_exec + 1] != FAIL )
	{
		// printf(BACK_RED"middle"RST"\n");
		// printf(BACK_CYAN"mini_sh->sep_type[i_exec + 1]: %i"RST"\n", mini_sh->sep_type[i_exec + 1]);
		// print_type(mini_sh->sep_type[i_exec + 1]);
		// if (mini_sh->sep_type[i_exec + 1] == PIPE)
		// 	mini_sh->exec->fd_out = mini_sh->exec->tab_fd[i_exec + 1][1];
		// if (mini_sh->sep_type[i_exec + 2] != FAIL && mini_sh->sep_type[i_exec + 2] == PIPE)
		// 	mini_sh->exec->fd_out = mini_sh->exec->tab_fd[i_exec + 2][1];
		// else if (mini_sh->sep_type[i_exec + 1] == REDIR_R)
		// 	mini_sh->exec->fd_out = mini_sh->exec->fd_r[mini_sh->exec->check_r];
		// else if (mini_sh->sep_type[i_exec + 1] == APPEND)
		// 	mini_sh->exec->fd_out = 
		// 	mini_sh->exec->fd_app[mini_sh->exec->check_app];
		do_good_redir(mini_sh, i_exec);
	}
	else //if (mini_sh->sep_type[i_exec + 1] == FAIL)
	{
		// printf(BACK_RED"else last "RST"\n");
		// print_type(mini_sh->sep_type[i_exec + 1]);
		// printf("i_exec = %d\n", i_exec);
		// printf("\n.....................................\n\n");
		// printf("mini_sh->exec->tab_fd[i_exec][1] = %d\n", mini_sh->exec->tab_fd[i_exec][1]);
		close(mini_sh->exec->tab_fd[i_exec][1]);
		// printf(BACK_PURPLE"mini_sh->exec->fd_in: %i"RST"\n", mini_sh->exec->fd_in);
		// printf("\n.....................................\n\n");
		mini_sh->exec->fd_out = 1;
	}
}

void	free_redir_l(t_mini_sh *mini_sh)
{
	if (mini_sh->exec->nbr_fd_l > 0)
		free(mini_sh->exec->fd_l);
}

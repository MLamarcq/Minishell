/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:56:38 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/28 14:06:52 by mlamarcq         ###   ########.fr       */
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

int	one_hr_multi_l(t_mini_sh *mini_sh)
{
	t_parse	*tmp;
	int	l_check;
	int	hr_check;

	l_check = FAIL;
	hr_check = FAIL;
	tmp = mini_sh->rl_out_head;
	while (tmp)
	{
		if (tmp->type == HR_DOC)
		{
			l_check = SUCCESS;
			break ;
		}
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (tmp->type == REDIR_L && tmp->next && tmp->next->next && tmp->next->next->type == REDIR_L)
			hr_check = SUCCESS;
		tmp = tmp->next;
	}
	if (l_check == SUCCESS && hr_check == SUCCESS)
		return (SUCCESS);
	return (FAIL);
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
	if (i == mini_sh->sep_2 - 1)
		return (FAIL);
	while (mini_sh->sep_type && mini_sh->sep_type[i] && i < mini_sh->sep_2)
	{
		if (mini_sh->sep_type[i] != REDIR_L && mini_sh->sep_type[i] != HR_DOC)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}


void	go_to_last_read_2(t_mini_sh *mini_sh, int i_exec)
{
	int	i_last_read;
	int check;
	int i;

	i = -1;
	i_last_read = i_exec;
	check = 0;
	while (mini_sh->sep_type[i_last_read] && (issep_write(mini_sh->sep_type[i_last_read]) == FAIL || mini_sh->sep_type[i_last_read] != FAIL) && (i_last_read < (mini_sh->sep_2)))
	{
		if (issep_read(mini_sh->sep_type[i_last_read]) == SUCCESS)
		{
			if (mini_sh->sep_type[i_last_read] == HR_DOC)
				i++;
			check = 1;
		}
		i_last_read++;
	}
	printf(RED"check = %d\n", check);
	if (check == 1)
	{
		print_type(mini_sh->sep_type[i_last_read]);
		if (mini_sh->sep_type && mini_sh->sep_type[i_last_read - 1] && mini_sh->sep_type[i_last_read - 1] == REDIR_L && mini_sh->exec->fd_l[i_last_read - 1])
			mini_sh->exec->fd_in = mini_sh->exec->fd_l[i_last_read - 1];
		else if (mini_sh->sep_type && mini_sh->sep_type[i_last_read - 1] && mini_sh->sep_type[i_last_read - 1] == HR_DOC)
		{
			close (mini_sh->exec->fd_hr[mini_sh->exec->check_hr + i]);
			printf(BACK_GREEN"mini_sh->exec->hr_name[mini_sh->exec->check_hr + i]: %s"RST"\n", mini_sh->exec->hr_name[mini_sh->exec->check_hr + i]);
			mini_sh->exec->fd_hr[mini_sh->exec->check_hr + i] = open(mini_sh->exec->hr_name[mini_sh->exec->check_hr + i], O_RDONLY, 0644);
			if (!mini_sh->exec->hr_name[mini_sh->exec->check_hr + i])
				return ; 
			mini_sh->exec->fd_in = mini_sh->exec->fd_hr[mini_sh->exec->check_hr + i];
		}
	}
}


void	do_redir_l(t_mini_sh *mini_sh, int i_exec)
{
	if (mini_sh->sep_2 && mini_sh->sep_type && (mini_sh->sep_2 == 1 || !mini_sh->sep_type[i_exec + 1]))
		close(mini_sh->exec->tab_fd[i_exec][1]);
	mini_sh->exec->fd_in = mini_sh->exec->fd_l[mini_sh->exec->check_l];
	if (mini_sh->sep_type && do_good_redir_l(mini_sh, i_exec) == SUCCESS && one_hr_multi_l(mini_sh) == FAIL)// mini_sh->sep_type[i_exec + 2] == FAIL)
	{
		printf(BACK_RED"start"RST"\n");
		// printf(BACK_CYAN"mini_sh->sep_type[i_exec + 1]: %i"RST"\n", mini_sh->sep_type[i_exec + 1]);
		// print_type(mini_sh->sep_type[i_exec + 1]);
		go_to_last_read_2(mini_sh, i_exec);
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
		//go_to_last_read_2(mini_sh, i_exec);
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

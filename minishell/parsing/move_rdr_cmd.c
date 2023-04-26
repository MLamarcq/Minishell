/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rdr_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:53:35 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/26 11:50:43 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

// void	prt(t_parse *tmp)
// {
// 	while (tmp)
// 	{
// 		print_word(tmp->word);
// 		if (tmp->type)
// 			print_type(tmp->type);
// 		tmp = tmp->next;
// 	}
// }

// t_parse	*extract_tmp(t_mini_sh *mini_sh)
// {
// 	t_parse *tmp;
// 	t_parse *temp;
	
// 	temp = mini_sh->rl_out_head;
// 	while (temp)
// 	{
// 		if (temp->prev && (temp->prev->type == ARG || temp->prev->type == EOFL || temp->prev->type == _FILE) && (temp->type == CMD || temp->type == CMD_ABS))
// 		{
// 			tmp = temp;
// 			// tmp = tmp->next;
// 			ft_lstclear(&tmp->next);
// 			//move_end_tmp(tmp);
// 			break ;
// 		}
// 		temp = temp->next;
// 	}
// 	printf("word = %s\n", tmp->word);
// 	printf("word = %p\n", tmp->next);
// 	return (tmp);
// }


// // void	move_end_tmp(t_parse *tmp)
// // {
	
// // }

// void	move_redir_cmd(t_mini_sh *mini_sh)
// {
// 	// int		i_mv_rdr;
// 	// int		thereis_cmd;
// 	// int		nbr_pipe;
// 	// int		nbr_pipe_chck;
// 	t_parse	*tmp;
// 	t_parse *temp;
	
// 	// t_parse	*tmp_2;

// 	// thereis_cmd = FAIL;
// 	// i_mv_rdr = 0;
// 	// nbr_pipe = 0;
// 	// nbr_pipe_chck = 0;
// 	tmp = NULL;
// 	// tmp_2 = NULL;
// 	mini_sh->rl_out = mini_sh->rl_out_head;
// 	tmp = extract_tmp(mini_sh);
// 	if (!tmp)
// 		return ;
// 	//printf("@word = %s\n", tmp->word);
// 	while (mini_sh->rl_out)
// 	{
// 		//printf("mini_sh->word = %s\n", mini_sh->rl_out->word);
// 	//	if (mini_sh->rl_out->prev && (mini_sh->rl_out->prev->type == ARG || mini_sh->rl_out->prev->type == EOFL || mini_sh->rl_out->prev->type == _FILE) && (mini_sh->rl_out->type == CMD || mini_sh->rl_out->type == CMD_ABS))
// 		if (mini_sh->rl_out->next && (issep_read(mini_sh->rl_out->next->type) == SUCCESS || issep_write(mini_sh->rl_out->next->type) == SUCCESS))
// 		{
// 			printf("mini_sh->rl_out->word: %s\n", mini_sh->rl_out->word);
// 			// temp = mini_sh->rl_out->next->next;
// 			// printf("temp = %s\n", temp->word);
// 			// printf(" mini_sh->rl_out->next = %s\n", mini_sh->rl_out->next->word);
// 			// mini_sh->rl_out->next = tmp;
// 			// printf(" mini_sh->rl_out->next = %s\n", mini_sh->rl_out->next->word);
// 			// tmp->next = temp;
			
// 			// print_word(mini_sh->rl_out->prev->word);
// 			// print_type(mini_sh->rl_out->prev->type);
// 			// print_word(mini_sh->rl_out->word);
// 			// print_type(mini_sh->rl_out->type);
// 			// printf(".....................................\n\n");
// 			// tmp = mini_sh->rl_out;
// 			// move_end_tmp(tmp);
			
// 		}
// 		mini_sh->rl_out = mini_sh->rl_out->next;
// 	}
// 	(void)tmp;
// 	(void)temp;
// }

// ls | << eof cat | wc -l

//try recursive


int	case_1(t_mini_sh *mini_sh)
{
	t_parse *tmp;
	
	set_index(mini_sh);
	mini_sh->rl_out = mini_sh->rl_out_head;
	while (mini_sh->rl_out)
	{
		if (is_all(mini_sh->rl_out->type) == SUCCESS)
		{
			//printf("youpi\n");
			tmp = mini_sh->rl_out->next;
			while (tmp && is_sep_int(tmp->type) == FAIL)
			{
			//	printf("tmp->type = %d\n", tmp->type);
				// print_type(tmp->type);
				// print_word(tmp->word);
				if (tmp->type == CMD || tmp->type == CMD_ABS)
				{
					// print_type(tmp->type);< 
					// print_word(tmp->word);
					return (SUCCESS);
				}
				tmp = tmp->next;
			}
		}
		mini_sh->rl_out = mini_sh->rl_out->next;
	}
	return (FAIL);
}

int	move_1(t_mini_sh *mini_sh)
{
	t_parse	*temp;
	t_parse	*tmp;
	t_parse	*tmp_2;
	t_parse	*tmp_3;
	
	temp = NULL;
	tmp = NULL;
	tmp_2 = NULL;
	tmp_3 = NULL;
	if (case_1(mini_sh) == FAIL)
		return (FAIL);
	//printf(BLUE"mini_sh->rl_out = %s\n"RST, mini_sh->rl_out->word);
	// mini_sh->rl_out = mini_sh->rl_out->next;
	while (mini_sh->rl_out->next && (mini_sh->rl_out->type != CMD && mini_sh->rl_out->type != CMD_ABS))
		mini_sh->rl_out = mini_sh->rl_out->next;
	// printf(GREEN"mini_sh->rl_out->prev = %s\n"RST, mini_sh->rl_out->prev->word);
	// printf("\n................................\n\n");
	// printf(YELLOW"mini_sh->rl_out->prev->prev->word = %s\n"RST, mini_sh->rl_out->prev->prev->word);
	// printf(YELLOW"mini_sh->rl_out->prev->word = %s\n"RST, mini_sh->rl_out->prev->word);
	// printf(GREEN"mini_sh->rl_out = %s\n"RST, mini_sh->rl_out->word);
	// printf(YELLOW"mini_sh->rl_out->next = %p\n"RST, mini_sh->rl_out->next);
	// printf("\n................................\n\n");
	// printf(PURPLE"mini_sh->rl_out->next->next = %s\n"RST, mini_sh->rl_out->next->next->word);
	
	if (mini_sh->rl_out->index != 0 && mini_sh->rl_out->index != 1)
	{
		tmp = mini_sh->rl_out->prev;
		temp = mini_sh->rl_out->prev->prev;
		tmp_2 = mini_sh->rl_out->next;
		if (mini_sh->rl_out->prev && mini_sh->rl_out->prev->prev && mini_sh->rl_out->prev->prev->prev)
			tmp_3 = mini_sh->rl_out->prev->prev->prev;
		
		mini_sh->rl_out->next = tmp;
		tmp->prev = mini_sh->rl_out;
		
		temp->next = mini_sh->rl_out;
		mini_sh->rl_out->prev = temp;
		
		tmp->next = tmp_2;
		if (mini_sh->rl_out->prev && mini_sh->rl_out->prev->prev && mini_sh->rl_out->prev->prev->prev)
		{
			tmp_3->next = temp;
			temp->prev = tmp_3;
		}
		
		// if (mini_sh->rl_out->next)
		// 	printf(BACK_GREEN"mini_sh->rl_out->next->word: %s"RST"\n", mini_sh->rl_out->next->word);
		// else
		// 	printf("good\n");

		if (mini_sh->rl_out->prev->prev)
			printf(BACK_GREEN"mini_sh->rl_out->prev->prev->word: %s"RST"\n", mini_sh->rl_out->prev->prev->word);
		else
			printf(BACK_GREEN"mini_sh->rl_out->prev->prev: %p"RST"\n", mini_sh->rl_out->prev->prev);
		if (mini_sh->rl_out->prev)
			printf(BACK_GREEN"mini_sh->rl_out->prev->word: %s"RST"\n", mini_sh->rl_out->prev->word);
		else
			printf(BACK_GREEN"mini_sh->rl_out->prev: %p"RST"\n", mini_sh->rl_out->prev);
		printf(BACK_GREEN"mini_sh->rl_out->word: %s"RST"\n", mini_sh->rl_out->word);
		if (mini_sh->rl_out->next)
			printf(BACK_GREEN"mini_sh->rl_out->next->word: %s"RST"\n", mini_sh->rl_out->next->word);
		else
			printf(BACK_GREEN"mini_sh->rl_out->next: %p"RST"\n", mini_sh->rl_out->next);
		if (mini_sh->rl_out->next && mini_sh->rl_out->next->next)
			printf(BACK_GREEN"mini_sh->rl_out->next->next->word: %s"RST"\n", mini_sh->rl_out->next->next->word);
		else
			printf(BACK_GREEN"mini_sh->rl_out->next->next: %p"RST"\n", mini_sh->rl_out->next->next);
		printf("\n");
		// printf("\n................................\n\n");
		// printf(YELLOW"mini_sh->rl_out->prev->prev->word = %s\n"RST, mini_sh->rl_out->prev->prev->word);
		// printf(YELLOW"mini_sh->rl_out->prev->word = %s\n"RST, mini_sh->rl_out->prev->word);
		// printf(YELLOW"mini_sh->rl_out = %s\n"RST, mini_sh->rl_out->word);
		// if (mini_sh->rl_out->next)
		// 	printf(YELLOW"mini_sh->rl_out->next = %s\n"RST, mini_sh->rl_out->next->word);
		// else
		// 	printf(YELLOW"mini_sh->rl_out->next = %p\n"RST, mini_sh->rl_out->next);
		// printf("\n................................\n\n");
	}
	else if (mini_sh->rl_out->index == 1)
	{
		tmp = mini_sh->rl_out->prev;
		temp = mini_sh->rl_out->next;
		if (mini_sh->rl_out->prev && mini_sh->rl_out->prev->prev)
			tmp_3 = mini_sh->rl_out->prev->prev; 
		
		mini_sh->rl_out->next = tmp;
		mini_sh->rl_out->prev = tmp->prev;
		tmp->prev = mini_sh->rl_out;
		
		tmp->next = temp;
		temp->prev = tmp;
		if (mini_sh->rl_out->prev && mini_sh->rl_out->prev->prev)
			tmp_3->next = mini_sh->rl_out;

		if (mini_sh->rl_out->prev)
			printf(BACK_YELLOW"mini_sh->rl_out->prev->word: %s"RST"\n", mini_sh->rl_out->prev->word);
		else
			printf(BACK_YELLOW"mini_sh->rl_out->prev: %p"RST"\n", mini_sh->rl_out->prev);
		printf(BACK_YELLOW"mini_sh->rl_out->word: %s"RST"\n", mini_sh->rl_out->word);
		if (mini_sh->rl_out->next)
			printf(BACK_YELLOW"mini_sh->rl_out->next->word: %s"RST"\n", mini_sh->rl_out->next->word);
		else
			printf(BACK_YELLOW"mini_sh->rl_out->next: %p"RST"\n", mini_sh->rl_out->next);
		if (mini_sh->rl_out->next && mini_sh->rl_out->next->next)
			printf(BACK_YELLOW"mini_sh->rl_out->next->next->word: %s"RST"\n", mini_sh->rl_out->next->next->word);
		else
			printf(BACK_YELLOW"mini_sh->rl_out->next->next: %p"RST"\n", mini_sh->rl_out->next->next);
		if (mini_sh->rl_out->next && mini_sh->rl_out->next->next && mini_sh->rl_out->next->next->next)
			printf(BACK_YELLOW"mini_sh->rl_out->next->next->next->word: %s"RST"\n", mini_sh->rl_out->next->next->next->word);
		else
			printf(BACK_YELLOW"mini_sh->rl_out->next->next->next: %p"RST"\n", mini_sh->rl_out->next->next->next);
		printf("\n");
		while (mini_sh->rl_out->prev)
		{
			printf(BACK_GREEN"mini_sh->rl_out->word: %s"RST"\n", mini_sh->rl_out->word);
			mini_sh->rl_out = mini_sh->rl_out->prev;
		}
		mini_sh->rl_out_head = mini_sh->rl_out;

	}
	//ft_print_rl_out(mini_sh);
	// printf(GREEN"tmp = %s\n"RST, tmp->word);
	// printf(GREEN"temp = %s\n"RST, temp->word);
	// printf(YELLOW"mini_sh->rl_out = %s\n"RST, mini_sh->rl_out->word);
	if (case_1(mini_sh) == SUCCESS)
		move_1(mini_sh);
	(void)temp;
	return (SUCCESS);
}

int	case_2(t_mini_sh *mini_sh)
{
	t_parse *tmp;
	
	set_index(mini_sh);
	mini_sh->rl_out = mini_sh->rl_out_head;
	while (mini_sh->rl_out)
	{
		if (is_all(mini_sh->rl_out->type) == SUCCESS)
		{
			tmp = mini_sh->rl_out->next;
			while (tmp && is_sep_int(tmp->type) == FAIL)
			{
				if ((tmp->type == CMD || tmp->type == CMD_ABS) && tmp->next->type == OPTION)
				{
					// print_type(tmp->type);
					// print_word(tmp->word);
					return (SUCCESS);
				}
				tmp = tmp->next;
			}
		}
		mini_sh->rl_out = mini_sh->rl_out->next;
	}
	return (FAIL);
}



// int move_2(t_mini_sh *mini_sh)
// {
// 	t_parse	*temp;
// 	t_parse	*tmp;
// 	t_parse	*tmp_2;
// 	t_parse	*tmp_3;
	
// 	temp = NULL;
// 	tmp = NULL;
// 	tmp_2 = NULL;
// 	tmp_3 = NULL;
// 	if (case_2(mini_sh) == FAIL)
// 		return (FAIL);
// 	//printf(BLUE"mini_sh->rl_out = %s\n"RST, mini_sh->rl_out->word);
// 	// mini_sh->rl_out = mini_sh->rl_out->next;
// 	while (mini_sh->rl_out->next && mini_sh->rl_out->type != OPTION)
// 		mini_sh->rl_out = mini_sh->rl_out->next;
// 	// printf(GREEN"mini_sh->rl_out->prev = %s\n"RST, mini_sh->rl_out->prev->word);
// 	// printf("\n................................\n\n");
// 	// printf(YELLOW"mini_sh->rl_out->prev->prev->word = %s\n"RST, mini_sh->rl_out->prev->prev->word);
// 	// printf(YELLOW"mini_sh->rl_out->prev->word = %s\n"RST, mini_sh->rl_out->prev->word);
// 	printf(GREEN"mini_sh->rl_out = %s\n"RST, mini_sh->rl_out->word);
// 	// printf(YELLOW"mini_sh->rl_out->next = %p\n"RST, mini_sh->rl_out->next);
// 	// printf("\n................................\n\n");
// 	// printf(PURPLE"mini_sh->rl_out->next->next = %s\n"RST, mini_sh->rl_out->next->next->word);
	
// 	if (mini_sh->rl_out->index != 0 && mini_sh->rl_out->index != 1)
// 	{
// 		printf(RED"mini_sh->rl_out = %s\n"RST, mini_sh->rl_out->word);
// 		tmp = mini_sh->rl_out->prev;
// 		printf(RED"tmp = %s\n"RST, tmp->word);
// 		temp = mini_sh->rl_out->prev->prev;
// 		printf(RED"temp = %s\n"RST, temp->word);
// 		if (mini_sh->rl_out->next)
// 			tmp_2 = mini_sh->rl_out->next;
		
		
// 		if (mini_sh->rl_out->prev && mini_sh->rl_out->prev->prev && mini_sh->rl_out->prev->prev->prev)
// 			tmp_3 = mini_sh->rl_out->prev->prev->prev;
		

// 		// if (mini_sh->rl_out->prev->prev)
// 		// 	printf(BACK_GREEN"mini_sh->rl_out->prev->prev->word: %s"RST"\n", mini_sh->rl_out->prev->prev->word);
// 		// else
// 		// 	printf(BACK_GREEN"mini_sh->rl_out->prev->prev: %p"RST"\n", mini_sh->rl_out->prev->prev);
// 		// if (mini_sh->rl_out->prev)
// 		// 	printf(BACK_GREEN"mini_sh->rl_out->prev->word: %s"RST"\n", mini_sh->rl_out->prev->word);
// 		// else
// 		// 	printf(BACK_GREEN"mini_sh->rl_out->prev: %p"RST"\n", mini_sh->rl_out->prev);
// 		// printf(BACK_GREEN"mini_sh->rl_out->word: %s"RST"\n", mini_sh->rl_out->word);
// 		// if (mini_sh->rl_out->next)
// 		// 	printf(BACK_GREEN"mini_sh->rl_out->next->word: %s"RST"\n", mini_sh->rl_out->next->word);
// 		// else
// 		// 	printf(BACK_GREEN"mini_sh->rl_out->next: %p"RST"\n", mini_sh->rl_out->next);
// 		// if (mini_sh->rl_out->next && mini_sh->rl_out->next->next)
// 		// 	printf(BACK_GREEN"mini_sh->rl_out->next->next->word: %s"RST"\n", mini_sh->rl_out->next->next->word);
// 		// else
// 		// 	printf(BACK_GREEN"mini_sh->rl_out->next->next: %p"RST"\n", mini_sh->rl_out->next->next);
// 		printf("\n");
		
		
		
// 		mini_sh->rl_out->next = tmp;
// 		tmp->prev = mini_sh->rl_out;
		
// 		temp->next = mini_sh->rl_out;
// 		mini_sh->rl_out->prev = temp;
		
// 		if (tmp_2)
// 			tmp->next = tmp_2;
// 		if (mini_sh->rl_out->prev && mini_sh->rl_out->prev->prev && mini_sh->rl_out->prev->prev->prev)
// 		{
// 			tmp_3->next = temp;
// 			temp->prev = tmp_3;
// 		}
// 	}
// 	// else if (mini_sh->rl_out->index == 1)
// 	// {
// 	// 	tmp = mini_sh->rl_out->prev;
// 	// 	temp = mini_sh->rl_out->next;
// 	// 	if (mini_sh->rl_out->prev && mini_sh->rl_out->prev->prev)
// 	// 		tmp_3 = mini_sh->rl_out->prev->prev; 
		
// 	// 	mini_sh->rl_out->next = tmp;
// 	// 	mini_sh->rl_out->prev = tmp->prev;
// 	// 	tmp->prev = mini_sh->rl_out;
		
// 	// 	tmp->next = temp;
// 	// 	temp->prev = tmp;
// 	// 	if (mini_sh->rl_out->prev && mini_sh->rl_out->prev->prev)
// 	// 		tmp_3->next = mini_sh->rl_out;

// 	// 	if (mini_sh->rl_out->prev)
// 	// 		printf(BACK_YELLOW"mini_sh->rl_out->prev->word: %s"RST"\n", mini_sh->rl_out->prev->word);
// 	// 	else
// 	// 		printf(BACK_YELLOW"mini_sh->rl_out->prev: %p"RST"\n", mini_sh->rl_out->prev);
// 	// 	printf(BACK_YELLOW"mini_sh->rl_out->word: %s"RST"\n", mini_sh->rl_out->word);
// 	// 	if (mini_sh->rl_out->next)
// 	// 		printf(BACK_YELLOW"mini_sh->rl_out->next->word: %s"RST"\n", mini_sh->rl_out->next->word);
// 	// 	else
// 	// 		printf(BACK_YELLOW"mini_sh->rl_out->next: %p"RST"\n", mini_sh->rl_out->next);
// 	// 	if (mini_sh->rl_out->next && mini_sh->rl_out->next->next)
// 	// 		printf(BACK_YELLOW"mini_sh->rl_out->next->next->word: %s"RST"\n", mini_sh->rl_out->next->next->word);
// 	// 	else
// 	// 		printf(BACK_YELLOW"mini_sh->rl_out->next->next: %p"RST"\n", mini_sh->rl_out->next->next);
// 	// 	if (mini_sh->rl_out->next && mini_sh->rl_out->next->next && mini_sh->rl_out->next->next->next)
// 	// 		printf(BACK_YELLOW"mini_sh->rl_out->next->next->next->word: %s"RST"\n", mini_sh->rl_out->next->next->next->word);
// 	// 	else
// 	// 		printf(BACK_YELLOW"mini_sh->rl_out->next->next->next: %p"RST"\n", mini_sh->rl_out->next->next->next);
// 	// 	while (mini_sh->rl_out->prev)
// 	// 	{
// 	// 		printf(BACK_GREEN"mini_sh->rl_out->word: %s"RST"\n", mini_sh->rl_out->word);
// 	// 		mini_sh->rl_out = mini_sh->rl_out->prev;
// 	// 	}
// 	// 	mini_sh->rl_out_head = mini_sh->rl_out;

// 	// }
// 	//ft_print_rl_out(mini_sh);
// 	// printf(GREEN"tmp = %s\n"RST, tmp->word);
// 	// printf(GREEN"temp = %s\n"RST, temp->word);
// 	// printf(YELLOW"mini_sh->rl_out = %s\n"RST, mini_sh->rl_out->word);
// 	if (case_2(mini_sh) == SUCCESS)
// 		move_2(mini_sh);
// 	(void)temp;
// 	return (SUCCESS);
// }


int	issep_read(int type)
{
	if (type == REDIR_L)
		return (SUCCESS);
	if (type == HR_DOC)
		return (SUCCESS);
	return (FAIL);
}

int	issep_write(int type)
{
	if (type == REDIR_R)
		return (SUCCESS);
	if (type == APPEND)
		return (SUCCESS);
	return (FAIL);
}

int is_all(int type)
{
	if (type == REDIR_R)
		return (SUCCESS);
	if (type == APPEND)
		return (SUCCESS);
	if (type == REDIR_L)
		return (SUCCESS);
	if (type == HR_DOC)
		return (SUCCESS);
	return (FAIL);
}
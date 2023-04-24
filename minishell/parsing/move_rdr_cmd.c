/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rdr_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:53:35 by ggosse            #+#    #+#             */
/*   Updated: 2023/04/24 16:57:18 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	prt(t_parse *tmp)
{
	while (tmp)
	{
		print_word(tmp->word);
		if (tmp->type)
			print_type(tmp->type);
		tmp = tmp->next;
	}
}

t_parse	*extract_tmp(t_mini_sh *mini_sh)
{
	t_parse *tmp;
	t_parse *temp;
	
	temp = mini_sh->rl_out_head;
	while (temp)
	{
		if (temp->prev && (temp->prev->type == ARG || temp->prev->type == EOFL || temp->prev->type == _FILE) && (temp->type == CMD || temp->type == CMD_ABS))
		{
			tmp = temp;
			// tmp = tmp->next;
			ft_lstclear(&tmp->next);
			//move_end_tmp(tmp);
			break ;
		}
		temp = temp->next;
	}
	printf("word = %s\n", tmp->word);
	printf("word = %p\n", tmp->next);
	return (tmp);
}


// void	move_end_tmp(t_parse *tmp)
// {
	
// }

void	move_redir_cmd(t_mini_sh *mini_sh)
{
	// int		i_mv_rdr;
	// int		thereis_cmd;
	// int		nbr_pipe;
	// int		nbr_pipe_chck;
	t_parse	*tmp;
	t_parse *temp;
	
	// t_parse	*tmp_2;

	// thereis_cmd = FAIL;
	// i_mv_rdr = 0;
	// nbr_pipe = 0;
	// nbr_pipe_chck = 0;
	tmp = NULL;
	// tmp_2 = NULL;
	mini_sh->rl_out = mini_sh->rl_out_head;
	tmp = extract_tmp(mini_sh);
	if (!tmp)
		return ;
	//printf("@word = %s\n", tmp->word);
	while (mini_sh->rl_out)
	{
		//printf("mini_sh->word = %s\n", mini_sh->rl_out->word);
	//	if (mini_sh->rl_out->prev && (mini_sh->rl_out->prev->type == ARG || mini_sh->rl_out->prev->type == EOFL || mini_sh->rl_out->prev->type == _FILE) && (mini_sh->rl_out->type == CMD || mini_sh->rl_out->type == CMD_ABS))
		if (mini_sh->rl_out->next && (issep_read(mini_sh->rl_out->next->type) == SUCCESS || issep_write(mini_sh->rl_out->next->type) == SUCCESS))
		{
			printf("mini_sh->rl_out->word: %s\n", mini_sh->rl_out->word);
			// temp = mini_sh->rl_out->next->next;
			// printf("temp = %s\n", temp->word);
			// printf(" mini_sh->rl_out->next = %s\n", mini_sh->rl_out->next->word);
			// mini_sh->rl_out->next = tmp;
			// printf(" mini_sh->rl_out->next = %s\n", mini_sh->rl_out->next->word);
			// tmp->next = temp;
			
			// print_word(mini_sh->rl_out->prev->word);
			// print_type(mini_sh->rl_out->prev->type);
			// print_word(mini_sh->rl_out->word);
			// print_type(mini_sh->rl_out->type);
			// printf(".....................................\n\n");
			// tmp = mini_sh->rl_out;
			// move_end_tmp(tmp);
			
		}
		mini_sh->rl_out = mini_sh->rl_out->next;
	}
	(void)tmp;
	(void)temp;
}

// ls | << eof cat | wc -l


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
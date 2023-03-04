/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_sep_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:03:49 by mael              #+#    #+#             */
/*   Updated: 2023/03/01 11:10:35 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../ft_minishell.h"

// int	first_is_sep(t_mini_sh *mini_sh)
// {
// 	printf("imput struct -> %s\n", mini_sh->output);
// 	if (mini_sh->output[0] == '|')
// 		return (SUCCESS);
// 	else if (mini_sh->output[0] == '>')
// 	{
// 		if (mini_sh->output[1] == '\0')
// 			return (FAIL);
// 		else
// 			return (SUCCESS);
// 	}
// 	else if (mini_sh->output[0] == '<')
// 		return (SUCCESS);
// 	return (FAIL);
// }

// int	last_is_sep(char *imput)
// {
// 	int len;

// 	len = ft_strlen(imput) - 1;
// 	if (imput[len] == '|')
// 		return (SUCCESS);
// 	else if (imput[len] == '>')
// 		return (SUCCESS);
// 	else if (imput[len] == '<')
// 		return (SUCCESS);
// 	return (FAIL);
// }

// int	count_sep(t_mini_sh *mini_sh, char *imput)
// {
// 	int i;

// 	if (!imput)
// 		return (FAIL);
// 	i = 0;
// 	while (imput[i])
// 	{
// 		if (imput[i] == '|')
// 			mini_sh->sep++;
// 		else if (imput[i] == '<' && imput[i + 1] == '<')
// 		{
// 			mini_sh->sep++;
// 			i++;
// 		}
// 		else if (imput[i] == '>' && imput[i + 1]  == '>')
// 		{
// 			mini_sh->sep++;
// 			i++;
// 		}
// 		else if (imput[i] == '>')
// 			mini_sh->sep++;
// 		else if (imput[i] == '<')
// 			mini_sh->sep++;
// 		i++;
// 	}
// 	return (SUCCESS);
// }

// int	init_sep(t_mini_sh *mini_sh, char *imput)
// {
// 	if (count_sep(mini_sh, imput) == FAIL)
// 		return (FAIL);
// 	if (first_is_sep(mini_sh) == SUCCESS)
// 		mini_sh->sep = mini_sh->sep - 1;
// 	if (last_is_sep(imput) == SUCCESS)
// 		mini_sh->sep = mini_sh->sep - 1;
// 	printf("res = %d\n", mini_sh->sep);
// 	return (SUCCESS);
// }

// // int	init_tab()

// //ls -la | grep -i | cat main.c > outfile << EOF >> ls
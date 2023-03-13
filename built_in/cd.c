/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:58:39 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/03/11 17:39:52 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

// int	ft_strlen(char *str)
// {
// 	int ite = 0;

// 	while (str[ite])
// 		ite++;
// 	return (ite):
// }

//  int	pwd(char *str)
// {
//  	printf("%s\n", getcwd(str, ft_strlen(str)));
// }

// void	ft_putstr(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		write(2, &str[i], 1);
// 		i++;
// 	}
// }

// int	prepare_cd(t_mini_sh *mini_sh)
// {
// 	int i;
// 	int j;
	
// 	i = 0;
// 	while (mini_sh->prepare_exec[i])
// 	{
// 		j = 0;
// 		while (mini_sh->prepare_exec[i][j])
// 		{
// 			if (ft_strncmp(mini_sh->prepare_exec[i][j], "cd", ft_strlen(mini_sh->prepare_exec[i][j])) == 0)
// 			{
// 				if (j == 0)
// 				{
// 					while (mini_sh->prepare_exec[i][j])
// 						j++
// 					if (j > 1)
// 					{
// 						printf("minishell: cd: too many arguments\n");
// 						return (FAIL);
// 					}
// 					return (SUCCESS);
// 				}
// 				else
// 					return (FAIL);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (FAIL);
// }

int	ft_cd(char **str)
{
	int	i;
	
	i = 0;
	if (ft_strncmp(str[0], "cd", 2) == 0)
	{
		while (str[i])
			i++;
		if (i > 1)
		{
			printf("minishell: cd: too many arguments");
			return (FAIL);
		}
		if (chdir(str[1]) == 0)
			return (SUCCESS);
		else
		{
			printf("bash: cd: %s: No such file or directory\n", str[2]);
			return (FAIL);
		}
	}
	else
			return (FAIL);
	return (FAIL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:58:39 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/02/18 16:58:47 by gael             ###   ########.fr       */
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

int	ft_cd(int argc, char **str)
{
	if (argc == 3)
	{
		if (ft_strncmp(str[1], "cd", 2) == 0)
		{
			if (chdir(str[2]) == 0)
			{
				printf("here\n");
				return (SUCCESS);
			}
			else
			{
				//perror("bash: cd:", ft_putstr(str[2]));
				printf("bash: cd: %s: No such file or directory\n", str[2]);
				return (FAIL);
			}
		}
		else
			return (FAIL);
	}
	else
		printf("bash: cd: too many arguments\n");
	return (FAIL);
}

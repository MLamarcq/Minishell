/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:34:48 by mael              #+#    #+#             */
/*   Updated: 2023/04/13 14:34:59 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	check_pwd_option(char **argv)
{
	if (argv[1][0] == '-')
	{
		printf("minishell: pwd: no option allowed\n");
		return (FAIL);
	}
	return (SUCCESS);
}

int	ft_pwd(char **argv)
{
	char	*str;

	str = NULL;
	if (check_pwd_option(argv) == FAIL)
		return (FAIL);
	if (ft_strncmp(argv[0], "pwd", 3) == 0)
	{
		str = getcwd(str, 10000);
		if (str != NULL)
			printf("%s\n", str);
		else
		{
			printf("Error during path finding\n");
			return (FAIL);
		}
		free(str);
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:34:48 by mael              #+#    #+#             */
/*   Updated: 2023/04/20 15:55:03 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int g_exit_stt;

int	check_pwd_option(char **argv)
{
	if (argv[1] && argv[1][0] == '-')
	{
		printf("minishell: pwd: no option allowed\n");
		g_exit_stt = 1;
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
		str = getcwd(NULL, 0);
		if (str != NULL)
			printf("%s\n", str);
		else
		{
			printf("Error during path finding\n");
			free (str);
			str = NULL;
			g_exit_stt = 1;
			return (FAIL);
		}
		free(str);
		str = NULL;
		g_exit_stt = 0;
	}
	return (SUCCESS);
}

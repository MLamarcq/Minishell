/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:34:48 by mael              #+#    #+#             */
/*   Updated: 2023/03/14 15:35:09 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_pwd(char **argv)
{
	char	*str;

	str = NULL;
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
		return (SUCCESS);
	}
	else
	{
		printf("%s: command not found\n", argv[0]);
		return (FAIL);
	}
}

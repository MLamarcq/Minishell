/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:26:23 by gael              #+#    #+#             */
/*   Updated: 2023/02/24 11:34:38 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

//main mael
// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	//(void)argv;
// 	//char *input;

// 	// while (1)
// 	// {
// 	// 	input = readline(">");
// 	// 	// process 
// 	// 	if (ft_strncmp(input, "exit", 4) == 0)
// 	// 		break ;
// 	// 	printf("input: %s\n", input);
// 	// }
// 	//printf("echo = %d\n", ft_echo(argv));
// 	ft_echo(argv);
// 	return (0);

// }


// main gael
int	main(int argc, char *argv[], char **envp)
{
	t_mini_sh	mini_sh;
	int	env_length;

	// mini_sh.env = envp;
	env_length = 0;
	while (envp[env_length])
		env_length++;
	mini_sh.env = (char **)malloc((sizeof (char *)) * (env_length + 1));
	env_length = -1;
	while (envp[++env_length])
	{
		mini_sh.env[env_length] = ft_strdup(envp[env_length]);
	}
	mini_sh.env[env_length] = 0;
	// printf("res 1 = %d\n", env_length);
	// env_length = 0;
	// while (mini_sh.env[env_length])
	// {
	// 	printf("-> %s\n", mini_sh.env[env_length]);
	// 	env_length++;
	// }
	// printf("res 2 = %d\n", env_length);
	// while (1)
	// {
		mini_sh.output = NULL;
		// ft_find_args(&mini_sh, "ls -l --color=never 	 -a | /usr/bin/grep -i --color=never  	   in >     result.txt");
		// mini_sh.output = readline("\n\033[31m>\033[0m");
		// printf(BLUE"mini_sh.output: %s\n"RESET, mini_sh.output);
		// printf("mini_sh.output[5]-48: %i\n", mini_sh.output[5]-48);
		// process 
		ft_find_args(&mini_sh);
	// 	if (ft_strncmp(mini_sh.output, "exit", 4) == 0)
	// 	{
	// 		char **str;
	// 		int res;

	// 		str = ft_split(mini_sh.output, ' ');
	// 		res = atoi(str[1]);
	// 		return (res);
	// 	}
	// }
	free_parsing(&mini_sh);
	free_env(&mini_sh);
	// env_length = -1;
	// while (mini_sh.env[++env_length])
	// {
	// 	free(mini_sh.env[env_length]);
	// }
	// free(mini_sh.env);
	(void)mini_sh;
	(void)argc;
	(void)argv;
	// return ((int)(mini_sh.output[5]));
	printf("here\n");
	return (0);
}
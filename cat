/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:43:09 by gael              #+#    #+#             */
/*   Updated: 2023/03/23 18:27:52 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	init_env_2(char **envp, t_mini_sh *mini_sh)
{
	int	env_length;

	env_length = 0;
	while (envp[env_length])
		env_length++;
	mini_sh->env = (char **)malloc((sizeof (char *)) * (env_length + 1));
	env_length = -1;
	while (envp[++env_length])
		mini_sh->env[env_length] = ft_strdup(envp[env_length]);
	mini_sh->env[env_length] = 0;
}

void	init_rl(t_mini_sh *mini_sh)
{
	mini_sh->output = readline("minishell>");
	mini_sh->sep = 0;
	mini_sh->sep_2 = 0;
	(void)mini_sh;
}

int	main(int argc, char *argv[], char **envp)
{
	t_mini_sh	mini_sh;

	mini_sh.output = NULL;
	init_env_2(envp, &mini_sh);
	while (1)
	{
		init_rl(&mini_sh);
		if (!mini_sh.output)
		{
			printf("@exit\n");
			break ;
		}
		if (mini_sh.output[0])
			add_history(mini_sh.output);
		exec_signal(1);
		if (ft_parsing(&mini_sh) == SUCCESS)
		{
			init_sep_type(&mini_sh);
			init_exec(&mini_sh);
			// if (mini_sh.sep_2 > 0)
			// {
			// 	printf("hehe22\n");
			// }
			init_tab_fd(&mini_sh);
			start_exec(&mini_sh);
			// if (do_built_in(&mini_sh) == FAIL)
			// 	exec_cmd(&mini_sh);
		}
		free(mini_sh.output),
		mini_sh.output = NULL;
		free_parsing(&mini_sh);
	}
	free_env(&mini_sh);
	(void)argc;
	(void)argv;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:10:09 by mael              #+#    #+#             */
/*   Updated: 2023/03/31 14:36:10 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	init_env(t_mini_sh *mini_sh)
{
	mini_sh->data = malloc(sizeof(t_env));
	if (!mini_sh->data)
		return (FAIL_MALLOC);
	mini_sh->data->env_sorted = NULL;
	mini_sh->data->dest = NULL;
	mini_sh->data->temp = NULL;
	mini_sh->data->size = envp_size(mini_sh->env);
	mini_sh->data->count = 0;
	mini_sh->data->ite_genv = 0;
	return (SUCCESS);
}

int	is_built_in_2(int i, t_mini_sh *mini_sh)
{
	if (ft_strncmp(mini_sh->prepare_exec[i][0], "echo", ft_strlen(mini_sh->prepare_exec[i][0])) == 0)
		return (ft_echo(mini_sh->prepare_exec[i]), SUCCESS);
	else if (ft_strncmp(mini_sh->prepare_exec[i][0], "pwd", ft_strlen(mini_sh->prepare_exec[i][0])) == 0)
		return (ft_pwd(mini_sh->prepare_exec[i]), SUCCESS);
	else if (ft_strncmp(mini_sh->prepare_exec[i][0], "cd", ft_strlen(mini_sh->prepare_exec[i][0])) == 0)
		return (ft_cd(mini_sh->prepare_exec[i], mini_sh), SUCCESS);
	else if (ft_strncmp(mini_sh->prepare_exec[i][0], "unset", ft_strlen(mini_sh->prepare_exec[i][0])) == 0)
		return (exec_unset(mini_sh->prepare_exec[i], mini_sh), SUCCESS);
	else if (ft_strncmp(mini_sh->prepare_exec[i][0], "export", ft_strlen(mini_sh->prepare_exec[i][0])) == 0)
	{
		if (!mini_sh->prepare_exec[i][1])
			print_export(mini_sh->prepare_exec[i], mini_sh);
		else
			export_arg(mini_sh->prepare_exec[i], mini_sh);
		return (SUCCESS);
	}
	else if (ft_strncmp(mini_sh->prepare_exec[i][0], "env", ft_strlen(mini_sh->prepare_exec[i][0])) == 0)
		return (env(mini_sh->prepare_exec[i], mini_sh), SUCCESS);
	return (FAIL);
}

int	do_built_in(t_mini_sh *mini_sh, int i)
{
//	int	i;

	init_env(mini_sh);
	init_env_sorted(mini_sh);
//	i = 0;
//	while (mini_sh->prepare_exec[i])
//	{
		if (is_built_in_2(i, mini_sh) == FAIL)
			return (FAIL);
//		i++;
//	}
	printf(BACK_GREEN"built"RST"\n");
	 //exit(1);
	return (SUCCESS);
}


// int	is_built_in_2(char **exec, t_mini_sh *mini_sh)
// {
// 	if (ft_strncmp(exec[0], "echo", ft_strlen(exec[0])) == 0)
// 		return (ft_echo(exec), SUCCESS);
// 	else if (ft_strncmp(exec[0], "pwd", ft_strlen(exec[0])) == 0)
// 		return (ft_pwd(exec), SUCCESS);
// 	else if (ft_strncmp(exec[0], "cd", ft_strlen(exec[0])) == 0)
// 		return (ft_cd(exec, mini_sh), SUCCESS);
// 	else if (ft_strncmp(exec[0], "unset", ft_strlen(exec[0])) == 0)
// 		return (exec_unset(exec, mini_sh), SUCCESS);
// 	else if (ft_strncmp(exec[0], "export", ft_strlen(exec[0])) == 0)
// 	{
// 		if (!exec[1])
// 			print_export(exec, mini_sh);
// 		else
// 			export_arg(exec, mini_sh);
// 		return (SUCCESS);
// 	}
// 	else if (ft_strncmp(exec[0], "env", ft_strlen(exec[0])) == 0)
// 		return (env(exec, mini_sh), SUCCESS);
// 	return (FAIL);
// }

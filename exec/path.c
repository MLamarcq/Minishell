/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:45:35 by mael              #+#    #+#             */
/*   Updated: 2023/03/14 15:45:36 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../ft_minishell.h"

// char	*find_cmd(t_mini_sh *mini_sh, int ite_env)
// {
// 	char	**path_cmd;
// 	char	*cmd_path_absolue;
// 	char	*path_absolue;
// 	char	*cmd;
// 	int		ite_data;

// 	ite_data = -1;
// 	path_cmd = ft_split(mini_sh->env[ite_env] + 5, ':');
// 	cmd = ft_strdup(mini_sh->rl_out->word);
// 	while (path_cmd[++ite_data])
// 	{
// 		path_absolue = ft_strjoin(path_cmd[ite_data], "/");
// 		cmd_path_absolue = ft_strjoin(path_absolue, cmd);
// 		free(path_absolue);
// 		if(access(cmd_path_absolue, X_OK) == 0)
// 		{
// 			// free(mini_sh->rl_out->word);
// 			// mini_sh->rl_out->word = ft_strdup(cmd_path_absolue);
// 			// mini_sh->rl_out->word[ft_strlen(cmd_path_absolue)] = '\0';
// 			free(cmd_path_absolue);
// 			free(cmd);
// 			// ft_free_all(cmd, path_cmd);
// 			return (SUCCESS);
// 		}
// 		else
// 			free(cmd_path_absolue);
// 	}
// 	ft_free_all(cmd, path_cmd);
// 	return (FAIL);
// }

// char	*find_path(t_mini_sh *mini_sh)
// {
// 	int	ite_env;

// 	ite_env = -1;
// 	while (mini_sh->env[++ite_env])
// 	{
// 		if (ft_strncmp(mini_sh->env[ite_env], "PATH=", 5) == 0)
// 			return (ft_find_cmd(mini_sh, ite_env));
// 	}
// 	return (FAIL);
// }
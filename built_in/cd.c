/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:58:39 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/03/14 11:58:39 by mael             ###   ########.fr       */
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

void	replace_pwd(t_mini_sh *mini_sh, int *is_exist, char *oldpwd)
{
	int i;
	char *new_pwd;
	
	new_pwd = getcwd(NULL, 10000);
	printf(BLUE"old = %s\n"RST, oldpwd);
	printf(RED"new= %s\n"RST, new_pwd);
	i = 0;
	while (mini_sh->env[i])
	{
		if (ft_strncmp(mini_sh->env[i], "PWD=", 3) == 0)
		{
			free(mini_sh->env[i]);
			mini_sh->env[i] = ft_strjoin_rfree("PWD=", new_pwd);
		}
		else if (ft_strncmp(mini_sh->env[i], "OLDPWD=", 6) == 0)
		{
			(*is_exist)++;
			free(mini_sh->env[i]);
			mini_sh->env[i] = oldpwd;
		}
		i++;
	}
}

int	export_cd(char **str, t_mini_sh *mini_sh)
{
	char	*dest;
	char	*oldpwd;
	int		is_exist;

	dest = getcwd(NULL, 10000);
	is_exist = 0;
	oldpwd = ft_strjoin("OLDPWD=", dest);
	if (chdir(str[1]) == 0)
		replace_pwd(mini_sh, &is_exist, oldpwd);
	else
		return (FAIL);
	if (is_exist == 0)
		export_specific(oldpwd, mini_sh);
	return (SUCCESS);
}

void	export_home(char *home, t_mini_sh *mini_sh)
{
	char	*dest;
	char	*oldpwd;
	int		is_exist;

	dest = getcwd(NULL, 10000);
	is_exist = 0;
	oldpwd = ft_strjoin("OLDPWD=", dest);
	if (chdir(home) == 0)
		replace_pwd(mini_sh, &is_exist, oldpwd);
	else
		printf("bash: cd: %s: No such file or directory\n", home);
	if (is_exist == 0)
		export_specific(oldpwd, mini_sh);
}

int	ft_cd(char **str, t_mini_sh *mini_sh)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
	if (ft_strncmp(str[0], "cd", 2) == 0)
	{
		// update OLD_PWD
		while (str[i])
			i++;
		//if (i == 1)
		if (i == 1)
		{
			home = ft_find_var_env(mini_sh->env, "HOME");
			printf(GREEN"here: %s\n"RST, home);
			if (home == NULL)
				return (printf("minishell: HOME not set"), FAIL);
			else
				export_home(home, mini_sh);
			return (FAIL);
		}
		if (i > 2)
		{
			printf("minishell: cd: too many arguments");
			return (FAIL);
		}
		if (export_cd(str, mini_sh) == FAIL)
		{
			printf("minishell: cd: %s: No such file or directory\n", str[1]);
			return (FAIL);
		}
		// if (chdir(str[1]) == 0)
		// 	return (SUCCESS);
		// // update PWD
		// else
		// {
		// }
	}
	else
			return (FAIL);
	return (SUCCESS);
}

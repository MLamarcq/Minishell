/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:58:39 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/03/14 15:43:33 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	replace_pwd(t_mini_sh *mini_sh, int *is_exist, char *oldpwd)
{
	int		i;
	char	*new_pwd;

	new_pwd = getcwd(NULL, 10000);
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

int	do_cd(int *i, char *home, char **str, t_mini_sh *mini_sh)
{
	if ((*i) == 1)
	{
		home = ft_find_var_env(mini_sh->env, "HOME");
		if (home == NULL)
			return (printf("minishell: HOME not set"), FAIL);
		else
			export_home(home, mini_sh);
		return (FAIL);
	}
	if ((*i) > 2)
	{
		printf("minishell: cd: too many arguments");
		return (FAIL);
	}
	if (export_cd(str, mini_sh) == FAIL)
	{
		printf("minishell: cd: %s: No such file or directory\n", str[1]);
		return (FAIL);
	}
	return (SUCCESS);
}

int	ft_cd(char **str, t_mini_sh *mini_sh)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
	if (ft_strncmp(str[0], "cd", 2) == 0)
	{
		while (str[i])
			i++;
		if (do_cd(&i, home, str, mini_sh) == FAIL)
			return (FAIL);
	}
	else
		return (FAIL);
	return (SUCCESS);
}

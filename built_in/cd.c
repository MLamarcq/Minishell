/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:58:39 by mlamarcq          #+#    #+#             */
/*   Updated: 2023/05/02 10:33:20 by mlamarcq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

extern int	g_exit_stt;

void	replace_pwd(t_mini_sh *mini_sh, int *is_exist, char *oldpwd)
{
	int		i;
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	i = 0;
	if (!oldpwd)
	{
		free(new_pwd);
		return ;
	}
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

	dest = getcwd(NULL, 0);
	is_exist = 0;
	if (!dest)
		return (printf("YO\n"), FAIL);
	oldpwd = ft_strjoin_rfree("OLDPWD=", dest);
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

	dest = getcwd(NULL, 0);
	is_exist = 0;
	if (dest)
		oldpwd = ft_strjoin_rfree("OLDPWD=", dest);
	else
		oldpwd = NULL;
	if (chdir(home) == 0)
		replace_pwd(mini_sh, &is_exist, oldpwd);
	else
		printf("bash: cd: %s: No such file or directory\n", home);
	if (home)
	{
		free(home);
		home = NULL;
	}
	if (is_exist == 0 && oldpwd)
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
		return (SUCCESS);
	}
	if ((*i) > 2)
	{
		printf("minishell: cd: too many arguments\n");
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
		{
			printf("salut\n");
			g_exit_stt = 1;
			return (FAIL);
		}
		g_exit_stt = 0;
	}
	else
		return (FAIL);
	return (SUCCESS);
}

#include "../ft_minishell.h"

int	init_env(t_mini_sh *mini_sh)
{
	// int size;
	// int i;

	mini_sh->data = malloc(sizeof(t_env));
	if (!mini_sh->data)
		return (FAIL_MALLOC);
	// i = 0;
	// size = envp_size(envp);
	// mini_sh->data->envp = (char**)malloc(sizeof(char *) * (size + 1));
	// if (!mini_sh->data->envp)
	// 	return (FAIL);
	// mini_sh->data->envp[size] = 0;
	// while (envp[i])
	// {
	// 	mini_sh->data->envp[i] = ft_strdup(envp[i]);
	// 	i++;
	// }
	mini_sh->data->dest = NULL;
	mini_sh->data->temp = NULL;
	mini_sh->data->size = envp_size(mini_sh->env);
	mini_sh->data->count = 0;
	mini_sh->data->ite_getenv = 0;
	return (SUCCESS);
}

int	is_built_in_2(char **exec, t_mini_sh *mini_sh)
{
	if (ft_strncmp(exec[0], "echo", ft_strlen(exec[0])) == 0)
	{
		ft_echo(exec);
		return (SUCCESS);
	}
	else if (ft_strncmp(exec[0], "pwd", ft_strlen(exec[0])) == 0)
	{
		ft_pwd(exec);
		return (SUCCESS);
	}
	else if (ft_strncmp(exec[0], "cd", ft_strlen(exec[0])) == 0)
	{
		ft_cd(exec);
		return (SUCCESS);
	}
	else if (ft_strncmp(exec[0], "unset", ft_strlen(exec[0])) == 0)
	{
		exec_unset(exec, mini_sh);
		return (SUCCESS);
	}
	else if (ft_strncmp(exec[0], "export", ft_strlen(exec[0])) == 0)
	{
		if (!exec[1])
			print_export(exec, mini_sh);
		else
			export_arg(exec, mini_sh);
		return (SUCCESS);
	}
	else if (ft_strncmp(exec[0], "env", ft_strlen(exec[0])) == 0)
	{
		env(exec, mini_sh);
		return (SUCCESS);
	}
	return (FAIL);
}

int	do_built_in(t_mini_sh *mini_sh)
{
	int i;

	init_env(mini_sh);
	i = 0;
	while (mini_sh->prepare_exec[i])
	{
		is_built_in_2(mini_sh->prepare_exec[i], mini_sh);
		i++;
	}
	return (SUCCESS);
}
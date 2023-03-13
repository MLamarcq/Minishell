#include "../ft_minishell.h"

void	to_empty_line(char **argv, t_mini_sh *mini_sh)
{
	int i;
	int	argv_len;
	char *env_content;

	i = 0;
	// env_content = getenv(argv[1]);
	env_content = ft_find_var_env(mini_sh->env, argv[1]);
	printf("getenv = %s\n", env_content);
	while (mini_sh->env[i])
	{
		if (ft_strncmp(mini_sh->env[i], argv[1], ft_strlen(argv[1]) - 1) == 0)
		{
			argv_len = ft_strlen(argv[1]) + 1;
			while (mini_sh->env[i][argv_len] == env_content[mini_sh->data->ite_getenv])
			{
				mini_sh->data->ite_getenv++;
				argv_len++;
				mini_sh->data->count++;
			}
			if ((mini_sh->data->count - 1) == ft_strlen(env_content))
			{
				ft_bzero(mini_sh->env[i], ft_strlen(mini_sh->env[i]));
				break ;
			}
		}
		i++;
	}
}

int unset(char **argv, t_mini_sh *mini_sh)
{
	// int i;
	// int j;
	// int k;
	// char *dest;

	// i = 0;
	// dest = getenv(argv[2]);
		if (ft_strncmp(argv[0], "unset", 5) == 0)
		{
			to_empty_line(argv, mini_sh);
			// while (data->envp[i])
			// {
			// 	if (ft_strncmp(data->envp[i], argv[2], ft_strlen(argv[2]) - 1) == 0)
			// 	{
			// 		j = 0;
			// 		k = ft_strlen(argv[2]) + 1;
			// 		while (data->envp[i][k] == dest[j])
			// 		{
			// 			k++;
			// 			j++;
			// 			data->count++;
			// 		}
			// 		if ((data->count - 1) == ft_strlen(dest))
			// 		{
			// 			ft_bzero(data->envp[i], ft_strlen(data->envp[i]));
			// 			break ;
			// 		}
			// 	}
			// 	i++;
			//}
		}
	return (SUCCESS);
}

int exec_unset(char **argv, t_mini_sh *mini_sh)
{
	int i;
	int j;

	i = 0;
	j = 0;
	unset(argv, mini_sh);
	while (mini_sh->env[i])
	{
		if (mini_sh->env[i][j] == '\0')
		{
			free(mini_sh->env[i]);
			while (mini_sh->env[i + 1])
			{
				mini_sh->env[i] = ft_strdup(mini_sh->env[i + 1]);
				free(mini_sh->env[i + 1]);
				i++;
			}
			mini_sh->env[i] = '\0';
		}
		i++;
	}
	return (SUCCESS);
}
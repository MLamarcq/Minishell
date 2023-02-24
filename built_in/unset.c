#include "../ft_minishell.h"

void	to_empty_line(char **argv, t_env *data)
{
	int i;
	int	argv_len;
	char *env_content;

	i = 0;
	env_content = getenv(argv[2]);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], argv[2], ft_strlen(argv[2]) - 1) == 0)
		{
			argv_len = ft_strlen(argv[2]) + 1;
			while (data->envp[i][argv_len] == env_content[data->ite_getenv])
			{
				data->ite_getenv++;
				argv_len++;
				data->count++;
			}
			if ((data->count - 1) == ft_strlen(env_content))
			{
				ft_bzero(data->envp[i], ft_strlen(data->envp[i]));
				break ;
			}
		}
		i++;
	}
}

int unset(int argc, char **argv, t_env *data)
{
	// int i;
	// int j;
	// int k;
	// char *dest;

	// i = 0;
	// dest = getenv(argv[2]);
	if (argc == 3)
	{
		if (ft_strncmp(argv[1], "unset", 5) == 0)
		{
			to_empty_line(argv, data);
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
	}
	return (SUCCESS);
}

int exec_unset(int argc, char **argv, t_env *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	unset(argc, argv, data);
	while (data->envp[i])
	{
		if (data->envp[i][j] == '\0')
		{
			free(data->envp[i]);
			while (data->envp[i + 1])
			{
				data->envp[i] = ft_strdup(data->envp[i + 1]);
				free(data->envp[i + 1]);
				i++;
			}
			data->envp[i] = '\0';
		}
		i++;
	}
	return (SUCCESS);
}
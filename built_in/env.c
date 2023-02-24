#include "../ft_minishell.h"

int	init_env(char **envp, t_env *data)
{
	int size;
	int i;

	i = 0;
	size = envp_size(envp);
	data->envp = (char**)malloc(sizeof(char *) * (size + 1));
	if (!data->envp)
		return (FAIL);
	data->envp[size] = 0;
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	data->dest = NULL;
	data->temp = NULL;
	data->size = envp_size(data->envp);
	data->count = 0;
	data->ite_getenv = 0;
	return (SUCCESS);
}

int	env(int argc, char **argv, t_env *data)
{
	int i;

	i = 0;
	if (argc == 2)
	{
		if (ft_strncmp(argv[1], "env", 3) == 0)
		{
			while (data->envp[i])
			{
				printf("%s\n", data->envp[i]);
				i++;
			}
			return (SUCCESS);
		}
		else
			printf("Command not found\n");
		return (FAIL);
	}
	else if (argc == 1)
		printf("To use env, only ./minishell env is allowed\n");
	else if (argc > 2 && (ft_strncmp(argv[1], "env", 3) == 0) && ft_strncmp(argv[2], "-", 1) != 0)
		printf("env: '%s': No such file or directory\n", argv[2]);
	else if (argc > 2 && (ft_strncmp(argv[1], "env", 3) == 0 && ft_strncmp(argv[2], "-", 1) == 0))
		printf("Options are not allowed with env for minishell\n");
	return (FAIL);
}

#include "../ft_minishell.h"

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

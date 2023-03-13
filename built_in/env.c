#include "../ft_minishell.h"

int	env(char **argv, t_mini_sh *mini_sh)
{
	// int i;
	int j;

	// i = 0;
	if (ft_strncmp(argv[0], "env", 3) == 0)
	{
		// while (argv[i])
		// 	i++;
		// if (i == 1 && (ft_strncmp(argv[1], "-", 1) != 0))
		// {
		// 	printf("env: '%s': No such file or directory\n", argv[1]);
		// 	return (FAIL);
		// }
		// else if (i == 1 && (ft_strncmp(argv[1], "-", 1) == 0))
		// {
		// 	printf("Options are not allowed with env for minishell\n");
		// 	return (FAIL);
		// }
		j = 0;
		while (mini_sh->env[j])
		{
			printf("%s\n", mini_sh->env[j]);
			j++;
		}
		return (SUCCESS);
	}
	else
		printf("Command not found\n");
	return (FAIL);
}
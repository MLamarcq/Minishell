#include "../ft_minishell.h"

// int	ft_strlen(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

int	ft_pwd(char **argv)
{
	char *str;

	str = NULL; 
	if (ft_strncmp(argv[1], "pwd", 3) == 0)
	{
		str = getcwd(str, 10000);
		if (str != NULL)
			printf("%s\n", str);
		else
		{
			printf("Error during path finding\n");
			return (FAIL);
		}
		free(str);
		return (SUCCESS);
	}
	else
	{
		printf("%s: command not found\n", argv[1]);
		return (FAIL);
	}
}

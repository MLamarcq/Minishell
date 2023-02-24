#include "../ft_minishell.h"

char	*ft_bzero(char *str, int len)
{
	int i;

	i = 0;
	//printf("temp = %s\n", str);
	while (i < len)
	{
		str[i] = '\0';
		i++;
	}
	//printf("temp = %s\n", str);
	//free(str);
	return (str);
}
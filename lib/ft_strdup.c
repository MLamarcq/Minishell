#include "../ft_minishell.h"

char    *ft_strdup(char *src)
{
	int i;
	char *dest;

	dest = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
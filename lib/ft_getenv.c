#include "../ft_minishell.h"

char	*ft_getenv(char *str)
{
	char *dest;

	dest = getenv(str);
	if (!dest)
		return (NULL);
	//printf("dest = %s\n", dest);
	return (dest);
}

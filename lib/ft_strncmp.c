#include "../ft_minishell.h"

int ft_strncmp(char *str, char *dest, int n)
{
    int i;

    i = 0;
    while ((str[i] == dest[i]) && i < n)
        i++;
    return (str[i] - dest[i]);
}

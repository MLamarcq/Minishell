#include "../ft_minishell.h"

int     envp_size(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        i++;
    return (i);
}
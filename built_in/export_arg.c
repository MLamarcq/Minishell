#include "../ft_minishell.h"

int	if_arg(char **argv, t_mini_sh *mini_sh)
{
	int i;

	i = 0;
	if (ft_strncmp(argv[0], "export", 6) == 0)
	{
		mini_sh->data->dest = ft_strdup(argv[1]);
		while (mini_sh->data->dest[i])
		{
			if (mini_sh->data->dest[i] == '=')
				return (SUCCESS);
			i++;
		}
	}
		return (FAIL);
}

void	ft_free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	export_arg(char **argv, t_mini_sh *mini_sh)
{
	int i;

	i = 0;
	if (if_arg(argv, mini_sh) == SUCCESS)
	{
		mini_sh->data->new_envp = (char **)malloc(sizeof (char *) * (mini_sh->data->size + 2));
		if (!mini_sh->data->new_envp)
			return (FAIL);
		mini_sh->data->new_envp[mini_sh->data->size + 1] = 0;
		i = -1;
		while (mini_sh->env[++i])
			mini_sh->data->new_envp[i] = ft_strdup(mini_sh->env[i]);
		mini_sh->data->new_envp[i] = ft_strdup(mini_sh->data->dest);
		ft_free_tab(mini_sh->env);
		mini_sh->env = (char **)malloc(sizeof (char *) * (mini_sh->data->size + 2));
		if (!mini_sh->env)
			return (FAIL);
		i = -1;
		while (mini_sh->data->new_envp[++i])
			mini_sh->env[i] = ft_strdup(mini_sh->data->new_envp[i]);
		mini_sh->env[mini_sh->data->size + 1] = 0;
		ft_free_tab(mini_sh->data->new_envp);
		export(argv, mini_sh);
		i = 0;
		while (mini_sh->env[i])
		{
			printf("-> %s\n", mini_sh->env[i]);
			i++;
		}
	}
	return (FAIL);
}
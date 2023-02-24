#include "../ft_minishell.h"

int	if_arg(int argc, char **argv, t_env *data)
{
	int i;

	i = 0;
	if (argc == 3)
	{
		if (ft_strncmp(argv[1], "export", 6) == 0)
		{
			data->dest = ft_strdup(argv[2]);
			while (data->dest[i])
			{
				if (data->dest[i] == '=')
					return (SUCCESS);
				i++;
			}
		}
		return (FAIL);
	}
	else
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

int	export_arg(int argc, char **argv, t_env *data)
{
	int i;

	i = 0;
	if (if_arg(argc, argv, data) == SUCCESS)
	{
		data->new_envp = (char **)malloc(sizeof (char *) * (data->size + 2));
		if (!data->new_envp)
			return (FAIL);
		data->new_envp[data->size + 1] = 0;
		i = -1;
		while (data->envp[++i])
			data->new_envp[i] = ft_strdup(data->envp[i]);
		data->new_envp[i] = ft_strdup(data->dest);
		ft_free_tab(data->envp);
		data->envp = (char **)malloc(sizeof (char *) * (data->size + 2));
		if (!data->envp)
			return (FAIL);
		i = -1;
		while (data->new_envp[++i])
			data->envp[i] = ft_strdup(data->new_envp[i]);
		data->envp[data->size + 1] = 0;
		ft_free_tab(data->new_envp);
		export_3(argc, argv, data);
		i = 0;
		while (data->envp[i])
		{
			printf("-> %s\n", data->envp[i]);
			i++;
		}
	}
	return (FAIL);
}
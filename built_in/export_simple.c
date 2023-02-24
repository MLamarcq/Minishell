#include "../ft_minishell.h"

int	is_sorted(t_env *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (data->envp[i + 1])
	{
		j = 0;
		if (data->envp[i][j] > data->envp[i + 1][j])
			return (FAIL);
		i++;
	}
	(void)j;
	return (SUCCESS);
}

void	swap_line(int i, t_env *data)
{
	data->temp = ft_strdup(data->envp[i]);
	free(data->envp[i]);
	data->envp[i] = ft_strdup(data->envp[i + 1]);
	free(data->envp[i + 1]);
	data->envp[i + 1] = ft_strdup(data->temp);
	free(data->temp);
}

void	sort_export(t_env *data)
{
	int i;
	int j;

	while (is_sorted(data) == FAIL)
	{
		i = 0;
		while (data->envp[i + 1])
		{
			j = 0;
			if (data->envp[i][j] > data->envp[i + 1][j])
				swap_line(i, data);
			else if (data->envp[i][j] == data->envp[i + 1][j])
			{
				while (data->envp[i][j] == data->envp[i + 1][j])
					j++;
				if (data->envp[i][j] > data->envp[i + 1][j])
					swap_line(i, data);
			}
			i++;
		}
	}
}

int	export_3(int argc, char **argv, t_env *data)
{
	if (argc == 2 || argc == 3)
	{
		if (ft_strncmp(argv[1], "export", 6) == 0)
			sort_export(data);
	}
	else
		return (FAIL);
	return (SUCCESS);
}


int	print_export(int argc, char **argv, t_env *data)
{
	int i;

	i = 0;
	if (argc == 2)
	{
		if (ft_strncmp(argv[1], "export", 6) == 0)
		{
			if (export_3(argc, argv, data) == SUCCESS)
			{
				while (data->envp[i])
				{
					printf("declare -x %s\n", data->envp[i]);
					i++;
				}
				ft_free_tab(data->envp);
				return (SUCCESS);
			}
			else
				printf("Export failed\n");
			return (FAIL);
		}
	}
	else
		printf("\n");
	return (FAIL);
}




// printf("dest inside = %c\n", data->dest[j]);
// 				printf("var = %c\n", data->envp[i][j]);
// 				if (data->dest[j] > data->envp[i][j])
// 				{
// 						printf("c2\n");
// 						temp = ft_strdup(data->dest);
// 						free(data->dest);
// 						data->dest = ft_strdup(data->envp[i]);
// 						free(data->envp[i]);
// 						data->envp[i] = ft_strdup(temp);
// 						free(temp);
// 				}
// 				else if (data->dest[j] == data->envp[i][j])
// 				{
// 					while (data->dest[j] == data->envp[i][j])
// 						j++;
// 					if (data->dest[j] > data->envp[i][j])
// 					{
// 						temp = ft_strdup(data->dest);
// 						free(data->dest);
// 						data->dest = ft_strdup(data->envp[i]);
// 						free(data->envp[i]);
// 						data->envp[i] = ft_strdup(temp);
// 						free(temp);
// 					}
// 				}
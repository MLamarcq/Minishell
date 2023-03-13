#include "../ft_minishell.h"

int	is_sorted(t_mini_sh *mini_sh)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (mini_sh->env[i + 1])
	{
		j = 0;
		if (mini_sh->env[i][j] > mini_sh->env[i + 1][j])
			return (FAIL);
		i++;
	}
	(void)j;
	return (SUCCESS);
}

void	swap_line(int i, t_mini_sh *mini_sh)
{
	mini_sh->data->temp = ft_strdup(mini_sh->env[i]);
	free(mini_sh->env[i]);
	mini_sh->env[i] = ft_strdup(mini_sh->env[i + 1]);
	free(mini_sh->env[i + 1]);
	mini_sh->env[i + 1] = ft_strdup(mini_sh->data->temp);
	free(mini_sh->data->temp);
}

void	sort_export(t_mini_sh *mini_sh)
{
	int i;
	int j;

	while (is_sorted(mini_sh) == FAIL)
	{
		i = 0;
		while (mini_sh->env[i + 1])
		{
			j = 0;
			if (mini_sh->env[i][j] > mini_sh->env[i + 1][j])
				swap_line(i, mini_sh);
			else if (mini_sh->env[i][j] == mini_sh->env[i + 1][j])
			{
				while (mini_sh->env[i][j] == mini_sh->env[i + 1][j])
					j++;
				if (mini_sh->env[i][j] > mini_sh->env[i + 1][j])
					swap_line(i, mini_sh);
			}
			i++;
		}
	}
}

int	export(char **argv, t_mini_sh *mini_sh)
{
	if (ft_strncmp(argv[0], "export", 6) == 0)
		sort_export(mini_sh);
	else
		return (FAIL);
	return (SUCCESS);
}


int	print_export(char **argv, t_mini_sh *mini_sh)
{
	int i;
	i = 0;

	if (ft_strncmp(argv[0], "export", 6) == 0)
	{
		if (export_3(argv, mini_sh) == SUCCESS)
		{
			while (mini_sh->env[i])
			{
				printf("declare -x %s\n", mini_sh->env[i]);
				i++;
			}
			//ft_free_tab(mini_sh->env);
			return (SUCCESS);
		}
		else
			printf("Export failed\n");
		return (FAIL);
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
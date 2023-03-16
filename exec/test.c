#include "../ft_minishell.h"

char	*ft_find_cmd_2(t_mini_sh *mini_sh, int ite_env, char *cmd_to_find)
{
	char	**path_cmd;
	char	*cmd_path_absolue;
	char	*path_absolue;
	char	*cmd;
	int		ite_data;

	ite_data = -1;
	path_cmd = ft_split(mini_sh->env[ite_env] + 5, ':');
	cmd = ft_strdup(cmd_to_find);
	while (path_cmd[++ite_data])
	{
		path_absolue = ft_strjoin(path_cmd[ite_data], "/");
		cmd_path_absolue = ft_strjoin(path_absolue, cmd);
		free(path_absolue);
		if (access(cmd_path_absolue, X_OK) == 0)
		{
			ft_free_all(cmd, path_cmd);
			//printf(GREEN"cmd = %s\n"RST, cmd_path_absolue);
			return (cmd_path_absolue);
		}
		else
			free(cmd_path_absolue);
	}
	ft_free_all(cmd, path_cmd);
	return (NULL);
}

char	*ft_find_path_2(t_mini_sh *mini_sh, char *cmd_to_find)
{
	int	ite_env;

	ite_env = -1;
	while (mini_sh->env[++ite_env])
	{
		if (ft_strncmp(mini_sh->env[ite_env], "PATH=", 4) == 0)
			return (ft_find_cmd_2(mini_sh, ite_env, cmd_to_find));
	}
	return (NULL);
}

void	test_exec(t_mini_sh *mini_sh, int i)
{
	char *str;

	str = ft_find_path_2(mini_sh, mini_sh->prepare_exec[0][0]);
	//printf(BLUE"str = %s\n"RST, str);
	if (access(mini_sh->prepare_exec[i][0], X_OK) == 0)
	{
		execve(mini_sh->prepare_exec[i][0], mini_sh->prepare_exec[i], mini_sh->env);
	}
	else if (str != NULL)
	{
		free(mini_sh->prepare_exec[i][0]);
		mini_sh->prepare_exec[i][0] = str;
		execve(str, mini_sh->prepare_exec[i], mini_sh->env);
	}
	else
	{
		printf("minishell:%s: command not found\n", mini_sh->prepare_exec[0][0]);
		exit (127);
	}
}

int	init_tab_fd(t_mini_sh *mini_sh)
{
	int i;

	i = 0;
	mini_sh->exec->tab_fd = malloc(sizeof(int *) * (mini_sh->sep_2 + 1));
	if (!mini_sh->exec->tab_fd)
		return (FAIL_MALLOC);
	
}

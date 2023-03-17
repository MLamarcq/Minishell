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

void	test_exec(t_mini_sh *mini_sh, int i_exec)
{
	char *str;

	str = ft_find_path_2(mini_sh, mini_sh->prepare_exec[i_exec][0]);
	//printf(BLUE"str = %s\n"RST, str);
	printf(BACK_GREEN"mini: %s"RST"\n", mini_sh->prepare_exec[i_exec][0]);
	if (access(mini_sh->prepare_exec[i_exec][0], X_OK) == 0)
	{
		close(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][0]);
		close(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][1]);
		execve(mini_sh->prepare_exec[i_exec][0], mini_sh->prepare_exec[i_exec], mini_sh->env);
	}
	else if (str != NULL)
	{
		close(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][0]);
		close(mini_sh->exec->tab_fd[mini_sh->exec->pipe_id][1]);
		free(mini_sh->prepare_exec[i_exec][0]);
		mini_sh->prepare_exec[i_exec][0] = str;
		execve(str, mini_sh->prepare_exec[i_exec], mini_sh->env);
	}
	else
	{
		printf("minishell:%s: command not found\n", mini_sh->prepare_exec[i_exec][0]);
		exit (127);
	}
}

int	count_pipe(t_mini_sh *mini_sh)
{
	int	i_count_pipe;
	int	i_sep_type;

	i_sep_type = 0;
	i_count_pipe = 0;
	while (mini_sh->sep_type[i_sep_type])
	{
		if (mini_sh->sep_type[i_sep_type] == PIPE)
			i_count_pipe++;
		i_sep_type++;
	}
	return (i_count_pipe);
}

int	init_tab_fd(t_mini_sh *mini_sh)
{
	int	i_init_fd;

	i_init_fd = 0;
	mini_sh->exec->tab_fd = malloc(sizeof(int *) * (count_pipe(mini_sh) + 1));
	mini_sh->exec->tab_fd[count_pipe(mini_sh)] = 0;
	if (!mini_sh->exec->tab_fd)
		return (FAIL_MALLOC);
	while (i_init_fd < count_pipe(mini_sh))
	{
		mini_sh->exec->tab_fd[i_init_fd] = malloc(sizeof(int) * 3);
		mini_sh->exec->tab_fd[i_init_fd][2] = 0;
		pipe(mini_sh->exec->tab_fd[i_init_fd]);
		printf(BACK_PURPLE"mini_sh->exec->tab_fd[%i][0]: %i"RST"\n", i_init_fd, mini_sh->exec->tab_fd[i_init_fd][0]);
		printf(BACK_PURPLE"mini_sh->exec->tab_fd[%i][1]: %i"RST"\n", i_init_fd, mini_sh->exec->tab_fd[i_init_fd][1]);
		i_init_fd++;
	}
	(void)i_init_fd;
	return (SUCCESS);
}

void	free_tab_fd(t_mini_sh *mini_sh)
{
	int	i_free_int;

	i_free_int = 0;
	while (mini_sh->exec->tab_fd[i_free_int])
	{
		close(mini_sh->exec->tab_fd[i_free_int][0]);
		close(mini_sh->exec->tab_fd[i_free_int][1]);
		free(mini_sh->exec->tab_fd[i_free_int]);
		i_free_int++;
	}
	free(mini_sh->exec->tab_fd);
}


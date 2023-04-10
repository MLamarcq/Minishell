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

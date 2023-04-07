#include "../ft_minishell.h"

void	count_redir_for_alloc(t_parse *tmp, t_mini_sh *mini_sh)
{
	if (tmp->type == REDIR_R)
		mini_sh->exec->nbr_fd_r++;
	else if (tmp->type == REDIR_L)
		mini_sh->exec->nbr_fd_l++;
	else if (tmp->type == APPEND)
		mini_sh->exec->nbr_fd_app++;
	else if (tmp->type == HR_DOC)
		mini_sh->exec->nbr_fd_hr++;
}

void	init_redir_fd(t_mini_sh *mini_sh)
{
	//printf("on init bien\n");
	if (mini_sh->exec->nbr_fd_r > 0)
		init_redir_r_tab(mini_sh);
	if (mini_sh->exec->nbr_fd_app > 0)
		init_append_tab(mini_sh);
	if (mini_sh->exec->nbr_fd_hr > 0)
		init_hr_dc_tab(mini_sh);
	if (mini_sh->exec->nbr_fd_l > 0)
		init_redir_l_tab(mini_sh);
}

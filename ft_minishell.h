/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:14:58 by gael              #+#    #+#             */
/*   Updated: 2023/02/21 11:59:46 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

// ------------------------------ include ----------------------------------- //
// ---------------------------- end include --------------------------------- //

// ------------------------------ define ------------------------------------ //
# define SUCCESS 1
# define FAIL -1
// ---------------------------- end define ---------------------------------- //

// ------------------------------ struct ------------------------------------ //

typedef struct s_list
{
	char				*line;
	int					index;
	struct s_list		*next;
}   t_list;

typedef struct s_env
{
	char	**envp;
	char	**new_envp;
	char	*dest;
	char	*temp;
	int		size;
	int 	count;
	int		ite_getenv;
}   t_env;
// ---------------------------- end struct ---------------------------------- //

//-------------------------------built_in-------------------------------------//

//env.c
int				env(int argc, char **argv, t_env *data);
int				init_env(char **envp, t_env *data);

//unset.c
int				exec_unset(int argc, char **argv, t_env *data);
void			to_empty_line(char **argv, t_env *data);
int				unset(int argc, char **argv, t_env *data);

//export_simple.c
int				export_3(int argc, char **argv, t_env *data);
int				is_sorted(t_env *data);
void			sort_export(t_env *data);
void			sort_algo(int i, t_env *data);
int				print_export(int argc, char **argv, t_env *data);

//export_arg.c
int				if_arg(int argc, char **argv, t_env *data);
int				export_arg(int argc, char **argv, t_env *data);

//built_in/cd.c
int				ft_cd(int argc, char **str);

//built_in/echo.c

int				ft_echo(char **str);
//built_in/pwd.c
int				ft_pwd(char **argv);
int				ft_strlen(char *str);

//------------------------------------lib-------------------------------------//

//lib/envp_size.c
int				envp_size(char **envp);

//lib/ft_strdup.c
char			*ft_strdup(char *src);

//lib/ft_getenv.c
char			*ft_getenv(char *str);

//lib/ft_strncmp.c
int				ft_strncmp(char *str, char *dest, int n);

//lib/bzero.c
char			*ft_bzero(char *str, int len);

//-----------------------------------parsing----------------------------------//

//parsing/ft_parsing.c
int				ft_quote(char *line);

void	ft_free_tab(char **tab);

#endif
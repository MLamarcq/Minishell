/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:14:58 by gael              #+#    #+#             */
/*   Updated: 2023/03/14 16:59:09 by mael             ###   ########.fr       */
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
# include "color.h"
// ---------------------------- end include --------------------------------- //

// ------------------------------ define ------------------------------------ //
# define SUCCESS 1
# define FAIL -1
# define FAIL_MALLOC -2
# define D_QUOTE 34
# define S_QUOTE 39
// ---------------------------- end define ---------------------------------- //

// ------------------------------ struct ------------------------------------ //

typedef struct s_list
{
	char				*line;
	int					index;
	struct s_list		*next;
}   t_list;

typedef struct s_arr_output
{
	char				*word;
	int					type;
	struct s_arr_output	*next;
}		t_parse;

// typedef struct s_mini_sh
// {
// 	char			*output;
// 	char			**env;
// 	char			***prepare_exec;
// 	t_parse	*rl_out;
// 	t_parse	*rl_out_head;
// }					t_mini_sh;

enum e_type
{
	CMD=2,
	CMD_ABS,
	PIPE,
	ARG,
	OPTION,
	REDIR_L,
	REDIR_R,
	_FILE,
	APPEND,
	HR_DOC,
	BUILT_IN
};

typedef struct s_exec_tools
{
	int	fd_R;
	int	fd_L;
	int	fd_HR;
	int	fd_APP;
	int	fd[2];
} t_exec_t;

typedef struct s_env
{
	char	**env_sorted;
	char	**new_envp;
	char	*dest;
	char	*temp;
	int		size;
	int 	count;
	int		ite_genv;
}   t_env;

typedef struct s_mini_sh
{
	char			*output;
	char			**env;
	char			***prepare_exec;
	int				is_dquote;
	int				is_squote;
	int				sep;
	int				flag;
	int				sep_2;
	int				nbr_word;
	int				*sep_type;
	pid_t			*pids;
	t_env			*data;
	t_exec_t		*exec;
	t_parse	*rl_out;
	t_parse	*rl_out_head;
}	t_mini_sh;

// ---------------------------- end struct ---------------------------------- //

//main.c
//signal/handle_ctrl_c.c
void			handle_ctrl_c(int signal);
//signal/exec_signal.c
void			exec_signal(int index);
//built_in/cd.c
int				ft_cd(char **str, t_mini_sh *mini_sh);
//built_in/unset.c
int				exec_unset(char **argv, t_mini_sh *mini_sh);
void			to_empty_line(char **argv, t_mini_sh *mini_sh);
int				unset(char **argv, t_mini_sh *mini_sh);
//built_in/echo.c
int				ft_echo(char **str);
//built_in/pwd.c
int				ft_pwd(char **argv);
//built_in/export_arg.c
int				export_arg(char **argv, t_mini_sh *mini_sh);
void			ft_free_tab(char **tab);
int				if_arg(char **argv, t_mini_sh *mini_sh);
//built_in/env.c
int				env(char **argv, t_mini_sh *mini_sh);
//built_in/export_simple.c
int				export(char **argv, t_mini_sh *mini_sh);
int				is_sorted(t_mini_sh *mini_sh);
int				print_export(char **argv, t_mini_sh *mini_sh);
void			sort_export(t_mini_sh *mini_sh);
void			swap_line(int i, t_mini_sh *mini_sh);
//lib/main.c
//lib/envp_size.c
int				envp_size(char **envp);
//lib/ft_cmp.c
int				ft_strcmp(char *str, char *dest);
int				ft_strncmp(char *str, char *dest, int n);
//lib/ft_lstnew_word.c
t_parse *ft_lstnew_malloc(int size);
t_parse *ft_lstnew_word(char *content, int save, int ite);
//lib/ft_lstadd_back.c
void			ft_lstadd_back(t_parse **lst, t_parse *new);
//lib/ft_strjoin.c
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strjoin_dfree(char *s1, char *s2);
char			*ft_strjoin_lfree(char *s1, char *s2);
char			*ft_strjoin_rfree(char *s1, char *s2);
//lib/ft_getenv.c
char			*ft_getenv(char *str);
//lib/ft_strlen.c
int				ft_strlen(char *str);
//lib/ft_is_separator.c
int				ft_is_sep_expand(char chr);
int				ft_is_sep_parse(char chr);
int				ft_is_valid_export(char chr);
int				ft_isalpha(int chr);
int				valid_identifier(int chr);
//lib/ft_split.c
char			**ft_split(const char *str, char sep);
//lib/bzero.c
char			*ft_bzero(char *str, int len);
//lib/ft_strdup.c
char			*ft_strdup(char *str);
char			*ft_strdup_len(char *str, int start, int end);
//free/free_parsing.c
void			free_env(t_mini_sh *mini_sh);
void			free_parsing(t_mini_sh *mini_sh);
void			ft_free_all(char *str, char **tab);
void			ft_lstclear(t_parse **lst);
//exec/prepare_exec.c
int				count_double_arr(t_mini_sh *mini_sh);
int				count_word_for_alloc(t_mini_sh *mini_sh, t_parse *rlout);
void			free_exec(t_mini_sh *mini_sh);
int				prepare_exec(t_mini_sh *mini_sh);
//exec/which_sep.c
int				if_redir_L(t_mini_sh *mini_sh);
int				if_redir_R(t_mini_sh *mini_sh);
int				init_exec(t_mini_sh *mini_sh);
//exec/path.c
char			*find_cmd(t_mini_sh *mini_sh, int ite_env);
char			*find_path(t_mini_sh *mini_sh);
//exec/sep.c
int				check_first_is_sep(t_mini_sh *mini_sh);
int				check_first_is_sep_2(t_mini_sh *mini_sh);
int				check_first_sep_error_2(t_mini_sh *mini_sh);
int				count_sep_2(t_mini_sh *mini_sh);
int				is_sep(char *word);
//parsing/expand.c
void			expand(t_mini_sh *mini_sh);
int				ft_isthere_dollar(t_mini_sh *mini_sh);
void			init_quote(t_mini_sh *mini_sh);
int				interpreted(t_mini_sh *mini_sh);
void			replace_dollar(t_mini_sh * mini_sh, int *i_replace);
void			toggle_quote(t_mini_sh *mini_sh, char chr);
//parsing/set_type.c
int				is_built_in(t_mini_sh *mini_sh);
int				set_type(t_mini_sh *mini_sh);
//parsing/remove_quote.c
int				coun_without_qt(char *str);
void			remove_quote(t_mini_sh *mini_sh);
char			*write_without_qt(char *str);
//parsing/quote.c
int				check_quote_is_closed(char *line);
void			count_quote_arg(char *line, int *ite, int quote);
int				count_word(char *line);
int				quote_is_closed(char *line, int *ite, int quote);
//parsing/ft_find_path.c
int				ft_find_cmd(t_mini_sh *mini_sh, int ite_env);
int				ft_find_env(t_mini_sh *mini_sh);
int				ft_find_path(t_mini_sh *mini_sh);
char			*ft_find_var_env(char **envp, char *var_search);
//parsing/parsing.c
int				build_result_output(t_mini_sh *mini_sh, char *line);
int				ft_parsing(t_mini_sh *mini_sh);
void			ft_print_rl_out(t_mini_sh *mini_sh);
void			print_word(char *new_w);
void			print_word2(char *new_w);
void			put_word_in_minish(t_mini_sh *mini_sh, char *line, int *save, int *ite);

int	init_sep_type(t_mini_sh *mini_sh);
int	do_built_in(t_mini_sh *mini_sh);
int	init_env(t_mini_sh *mini_sh);
int				is_built_in_2(char **exec, t_mini_sh *mini_sh);
int init_env_sorted(t_mini_sh *mini_sh);
int	export_cd(char **str, t_mini_sh *mini_sh);
int	export_specific(char *to_export, t_mini_sh *mini_sh);
void	export_home(char *home, t_mini_sh *mini_sh);


void	fill_little_tab(t_mini_sh *mini_sh, int	trple);
// int	init_little_tab(t_mini_sh *mini_sh);
// int	init_big_tab(t_mini_sh *mini_sh);
// int	fill_little_tab(t_parse *tmp, int *dble, int *triple, t_mini_sh *mini_sh);

#endif
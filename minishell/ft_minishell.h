/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:14:58 by gael              #+#    #+#             */
/*   Updated: 2023/04/28 14:39:51 by mlamarcq         ###   ########.fr       */
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
}						t_list;

typedef struct s_arr_output
{
	char				*word;
	int					type;
	int					index;
	struct s_arr_output	*next;
	struct s_arr_output	*prev;
}						t_parse;

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
	BUILT_IN,
	EOFL,
	_DIR,
};

typedef struct s_exec_tools
{
	int		pipe_id;
	int		fd_in;
	int		fd_out;
	int		nbr_fd_r;
	int		nbr_fd_l;
	int		nbr_fd_hr;
	int		nbr_fd_app;
	int		*fd_r;
	int		ana_r;
	int		check_r;
	int		*fd_l;
	int		ana_l;
	int		check_l;
	int		*fd_app;
	int		ana_app;
	int		check_app;
	int		*fd_hr;
	char	**hr_name;
	int		check_hr;
	int		ana_hr;
	int		fd[2];
	int		**tab_fd; 
	int		already_hr;
	int		already_l;
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
}			t_env;

typedef struct s_mini_sh
{
	int			check;
	int			redir_alone;
	int 		sep_id;
	char		*file_heredoc;
	int			*hr_doc_tab;
	char		*output;
	char		**env;
	char		***prepare_exec;
	int			len_prepare_exec;
	int			is_dquote;
	int			is_squote;
	int			check_redir;
	int			sep;
	int			flag;
	int			sep_2;
	int			nbr_word;
	int			thereis_pipe;
	int			*sep_type;
	pid_t		*pids;
	t_env		*data;
	t_exec_t	*exec;
	t_parse		*rl_check_redir;
	t_parse		*rl_out;
	t_parse		*rl_out_head;
}				t_mini_sh;
// ---------------------------- end struct ---------------------------------- //

//signal/exec_signal.c
void	exec_signal(int index);
void	handle_sigint_2(int sig);
void	handle_sigquit(int sig);
//signal/handle_ctrl_c.c
void	handle_ctrl_c(int signal);
//main.c
void	init_env_2(char **envp, t_mini_sh *mini_sh);
void	init_rl(t_mini_sh *mini_sh);
//parsing/expand.c
void	exit_code(t_mini_sh *mini_sh);
void	expand(t_mini_sh *mini_sh);
int		ft_isthere_dollar(t_mini_sh *mini_sh, int *i_isdollar);
void	inside_expand(t_mini_sh *mini_sh, int *save, int *i_dollar, char *dest);
void	toggle_quote(t_mini_sh *mini_sh, char chr);
//parsing/print.c
void	ft_print_rl_out(t_mini_sh *mini_sh);
void	print_type(int type);
void	print_word(char *new_w);
void	print_word2(char *new_w);
//parsing/ft_find_path.c
int		ft_find_cmd(t_mini_sh *mini_sh, int ite_env);
int		ft_find_env(t_mini_sh *mini_sh);
int		ft_find_path(t_mini_sh *mini_sh);
//parsing/str_wo_qt.c
void	first_part(char *str, int *i_start, int *i_end, int *i_act);
void	last_part(char *str, int *i_start, int *i_act, int last_qt);
void	repeat_part(char **str_wo_qt, char *str, int i_start, int i_end);
void	second_part(char *str, int *last_qt, int *i_act);
char	*write_without_qt_2(char *str);
//parsing/move_rdr_cmd.c
int		case_1(t_mini_sh *mini_sh);
int		case_2(t_mini_sh *mini_sh);
int		case_3(t_mini_sh *mini_sh);
int		is_all(int type);
int		issep_read(int type);
int		issep_write(int type);
int		move_1(t_mini_sh *mini_sh);
int		move_2(t_mini_sh *mini_sh);
int		move_3(t_mini_sh *mini_sh);
//parsing/glue_redirl.c
void	detect_redirl_glue(t_mini_sh *mini_sh, int *is_did, int *glue, int ite);
void	detect_redirl_glue_2(t_mini_sh *mini_sh, int *is_did, int *glue, int ite);
void	glue_redirl(t_mini_sh *mini_sh);
void	set_after_glue_redirl(t_mini_sh *mini_sh, int glue);
//parsing/glue_pipe.c
void	detect_space_glue(t_mini_sh *mini_sh, int *is_did, int *glue, int ite);
void	glue_pipe(t_mini_sh *mini_sh);
void	set_after_glue_pipe(t_mini_sh *mini_sh, int glue);
//parsing/glue_hrdoc.c
void	detect_hrdoc_glue(t_mini_sh *mini_sh, int *is_did, int *glue, int ite);
void	detect_hrdoc_glue_2(t_mini_sh *mini_sh, int *is_did, int *glue, int ite);
void	glue_hrdoc(t_mini_sh *mini_sh);
void	set_after_glue_hrdoc(t_mini_sh *mini_sh, int glue);
//parsing/remove_quote_2.c
int		isthere_quote(t_mini_sh *mini_sh);
void	remove_quote_2(t_mini_sh *mini_sh);
//parsing/replace_dollar.c
void	replace_dollar(t_mini_sh *mini_sh, int *i_replace);
void	start_rplc_dlr(t_mini_sh *mini_sh, int *save, int *save2, int *i_rplc);
//parsing/quote.c
int		check_quote_is_closed(char *line);
void	count_quote_arg(char *line, int *ite);
void	init_quote(t_mini_sh *mini_sh);
int		quote_is_closed(char *line, int *ite, int quote);
//parsing/redir_error_1.c
int		check_redi_r_append_error(t_mini_sh *mini_sh);
int		check_redi_r_append_error_1(t_mini_sh *mini_sh);
int		check_redi_r_append_error_2(t_mini_sh *mini_sh);
int		print_error(int index, t_parse *tmp);
//parsing/set_index.c
void	set_index(t_mini_sh *mini_sh);
//parsing/glue_redirr.c
void	detect_redirr_glue(t_mini_sh *mini_sh, int *is_did, int *glue, int ite);
void	detect_redirr_glue_2(t_mini_sh *mini_sh, int *is_did, int *glue, int ite);
void	glue_redirr(t_mini_sh *mini_sh);
void	set_after_glue_redirr(t_mini_sh *mini_sh, int glue);
//parsing/redir_error_2.c
int		check_redir_follow(t_mini_sh *mini_sh);
int		redir_l_error(t_mini_sh *mini_sh);
//parsing/parsing.c
int		build_result_output(t_mini_sh *mini_sh, char *line);
int		check_rdr_follow(t_mini_sh *mini_sh);
int		ft_parsing(t_mini_sh *mini_sh);
int		is_built_in(t_mini_sh *mini_sh);
void	put_word_in_minish(t_mini_sh *mini, char *lne, int *sv, int *ite);
//parsing/glue_append.c
void	detect_app_glue(t_mini_sh *mini_sh, int *is_did, int *glue, int ite);
void	detect_app_glue_2(t_mini_sh *mini_sh, int *is_did, int *glue, int ite);
void	glue_app(t_mini_sh *mini_sh);
void	set_after_glue_app(t_mini_sh *mini_sh, int glue);
//parsing/set_type.c
int		set_type(t_mini_sh *mini_sh);
void	type_utils_1(t_mini_sh *mini_sh);
int		type_utils_2(t_mini_sh *mini_sh);
int		type_utils_3(t_mini_sh *mini_sh);
int		type_utils_4(t_mini_sh *mini_sh);
//parsing/find_var_env.c
char	*attr_var_found(char **envp, int ite_env, int ite_env_char, int save);
char	*build_var_env(char *var_env, char *var_search, int *ite_env_char);
char	*ft_find_var_env(char **envp, char *var_search);
void	init_res_var(char **res_varenv, int *save, int *i_char, int *i_env);
//parsing/set_type_utils.c
void	toggle_ti_pipe(t_mini_sh *mini_sh);
//exec/prepare_exec.c
int		count_word_for_alloc(t_mini_sh *mini_sh, t_parse *rlout);
int		prepare_exec(t_mini_sh *mini_sh);
//exec/expand_hrdoc.c
void	hrdoc_exit_code(char **word);
void	hrdoc_expand(t_mini_sh *mini_sh, char **word);
int		hrdoc_ft_isthere_dollar(t_mini_sh *mini_sh, char *word, int *i_isdollar);
//exec/which_sep.c
int		init_exec(t_mini_sh *mini_sh);
//exec/first_sep.c
int		check_first_is_sep(t_mini_sh *mini_sh);
int		check_first_is_sep_2(t_mini_sh *mini_sh);
int		check_first_sep_error_2(t_mini_sh *mini_sh);
//exec/redir_r.c
void	analyse_redir_before_alloc(t_mini_sh *mini_sh, t_parse *tmp);
void	change_nbr_r(t_mini_sh *mini_sh);
void	do_redir_r(t_mini_sh *mini_sh, int i_exec);
void	free_redir_r(t_mini_sh *mini_sh);
int		init_redir_r_tab(t_mini_sh *mini_sh);
void	when_append_after(t_mini_sh *mini_sh, int i);
//exec/heredoc_2.c
void	analyse_hrdoc_before_alloc(t_mini_sh *mini_sh, t_parse *tmp);
void	change_hr_doc(t_mini_sh *mini_sh);
void	do_heredoc(t_mini_sh *mini_sh, int i, t_parse *tmp);
void	do_heredoc_redir(t_mini_sh *mini_sh, int i_exec);
int		exec_all_hr_doc(t_mini_sh *mini_sh);
void	free_hr_doc(t_mini_sh *mini_sh);
void	go_to_last_read(t_mini_sh *mini_sh, int i_exec);
int		init_hr_dc_tab(t_mini_sh *mini_sh);
int		one_l_multi_hr(t_mini_sh *mini_sh);
void	unlink_hr_dc(t_mini_sh *mini_sh);
//exec/exit.c
void	exit_status(t_mini_sh *mini_sh, int i_exec);
//exec/init_fd.c
void	count_redir_for_alloc(t_parse *tmp, t_mini_sh *mini_sh);
void	init_redir_fd(t_mini_sh *mini_sh);
//exec/sep_test.c
void	if_hr_doc(t_mini_sh *mini_sh);
//exec/exec_utils.c
void	fill_little_tab(t_mini_sh *mini_sh, int trple);
int		init_big_tab(t_mini_sh *mini_sh);
//exec/redir_l.c
void	analyse_redir_before_alloc_2(t_mini_sh *mini_sh, t_parse *tmp);
void	change_nbr_l(t_mini_sh *mini_sh);
void	do_good_redir(t_mini_sh *mini_sh, int i_exec);
int		do_good_redir_l(t_mini_sh *mini_sh, int i_exec);
void	do_redir_l(t_mini_sh *mini_sh, int i_exec);
void	free_redir_l(t_mini_sh *mini_sh);
void	go_to_last_read_2(t_mini_sh *mini_sh, int i_exec);
int		init_redir_l_tab(t_mini_sh *mini_sh);
int		one_hr_multi_l(t_mini_sh *mini_sh);
//exec/start_exec_2.c
void	child_process(t_mini_sh *mini_sh, int i_exec);
void	close_all(t_mini_sh *mini_sh);
void	close_rdr(int *tab_rdr, int nbr_rdr);
int		count_redir_in_line(t_mini_sh *mini_sh, int type);
int		exec_builtin(t_mini_sh *mini_sh, int i);
void	exec_cmd(t_mini_sh *mini_sh, int i_exec);
int		exec_redir(t_mini_sh *mini_sh, int i_exec);
int		first_is_a_redir(t_mini_sh *mini_sh);
void	increase_check(t_mini_sh *mini_sh, int i_exec, int type);
int		init_fd_exec(t_mini_sh *mini_sh, int i_exec);
int		init_sep_type(t_mini_sh *mini_sh);
int		init_tab_fd(t_mini_sh *mini_sh);
int		is_there_a_redir(t_mini_sh *mini_sh);
void	print_cmd_not_found(t_mini_sh *mini_sh, int i_exec);
int		start_exec(t_mini_sh *mini_sh);
void	travel_through_the_read(t_mini_sh *mini_sh, int i_exec);
//exec/child_process.c
char	*ft_find_cmd_2(t_mini_sh *mini_sh, int ite_env, char *cmd_to_find);
char	*ft_find_path_2(t_mini_sh *mini_sh, char *cmd_to_find);
//exec/append.c
void	analyse_append_before_alloc(t_mini_sh *mini_sh, t_parse *tmp);
void	change_nbr_append(t_mini_sh *mini_sh);
void	do_append(t_mini_sh *mini_sh, int i_exec);
void	free_append(t_mini_sh *mini_sh);
int		init_append_tab(t_mini_sh *mini_sh);
int		init_fd_app(t_mini_sh *mini_sh, t_parse **tmp, int *i);
void	when_redir_r_after(t_mini_sh *mini_sh, int i);
//exec/sep.c
int		count_sep_2(t_mini_sh *mini_sh);
void	is_redir_alone(t_mini_sh *mini_sh);
int		is_sep(char *word);
int		is_sep_int(int type);
//exec/expand_hrdoc_utils.c
void	hrdoc_replace_dollar(t_mini_sh *mini_sh, char **word, int *i_replace);
void	hrdoc_start_rplc_dlr(char **word, int *sv, int *sv2, int *i_rplc);
//exec/heredoc.c
int		do_simple_heredoc(t_mini_sh *mini_sh, int i_exec);
int		init_heredoc(t_mini_sh *mini_sh);
int		init_tab_hrdoc(t_mini_sh *mini_sh, int j);
int		there_is_a_heredoc(t_mini_sh *mini_sh, int i_exec);
//free/free_all.c
void	free_all(t_mini_sh *mini_sh);
void	free_all_redir(t_mini_sh *mini_sh);
void	free_each_prpt(t_mini_sh *mini_sh);
//free/free_env.c
void	free_data(t_mini_sh *mini_sh);
void	free_env(t_mini_sh *mini_sh);
void	free_env_sorted(t_mini_sh *mini_sh);
//free/free_exec.c
void	free_exec(t_mini_sh *mini_sh);
void	free_prep_exec(t_mini_sh *mini_sh);
void	free_tab_fd(t_mini_sh *mini_sh);
//free/free_parsing.c
void	free_parsing(t_mini_sh *mini_sh);
void	ft_free_all(char *str, char **tab);
void	ft_free_var_env(char *var_env, char *res_var_env);
void	ft_lstclear(t_parse **lst);
//lib/ft_cmp.c
int		ft_strcmp(char *str, char *dest);
int		ft_strncmp(char *str, char *dest, int n);
//lib/ft_lstnew_word.c
t_parse *ft_lstnew_word(char *content, int save, int ite);
//lib/ft_lstadd_back.c
void	ft_lstadd_back(t_parse **lst, t_parse *new);
//lib/bzero.c
char	*ft_bzero(char *str, int len);
//lib/ft_strlen.c
int		ft_strlen(char *str);
//lib/ft_putstr_fd.c
void	ft_putstr_fd(char *s, int fd);
//lib/ft_atoi.c
int		ft_atoi(char *str);
//lib/ft_itoa.c
char	*ft_itoa(int n);
int		ft_itoa_len(int n);
//lib/ft_strjoin.c
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_dfree(char *s1, char *s2);
char	*ft_strjoin_lfree(char *s1, char *s2);
char	*ft_strjoin_rfree(char *s1, char *s2);
//lib/ft_split.c
char	**ft_split(const char *str, char sep);
//lib/ft_is_separator.c
int		ft_is_sep_expand(char chr);
int		ft_is_sep_parse(char chr);
int		ft_is_valid_export(char chr);
int		ft_isalpha(int chr);
int		valid_id(int chr);
//lib/ft_getenv.c
char	*ft_getenv(char *str);
//lib/ft_strdup.c
char	*ft_strdup(char *str);
char	*ft_strdup_len(char *str, int start, int end);
//lib/envp_size.c
int		envp_size(char **envp);
//lib/ft_is_digit.c
int		ft_isdigit(int c);
//built_in/unset.c
int		check_unset_error(char **argv);
int		exec_unset(char **argv, t_mini_sh *mini_sh);
int		to_empty_line(char **argv, t_mini_sh *mini_sh);
int		unset(char **argv, t_mini_sh *mini_sh);
//built_in/empty_line_utils.c
void	end_empty_line(char **env_ctt);
void	strcmp_empty_line(t_mini_sh *mini, char **dest, int *i, char **env_ctt);
void	to_empty_line_utils(t_mini_sh *mini_sh, int *len, int *j);
//built_in/export_arg.c
int		alloc_new_tab(t_mini_sh *mini_sh);
int		export_arg(char **argv, t_mini_sh *mini_sh);
int		realloc_tab(int *i, t_mini_sh *mini_sh);
int		realloc_tab_util(t_mini_sh *mini_sh, int *check, int *i);
//built_in/exit.c
void	check_arg(t_mini_sh *mini_sh);
int		check_num(char **tab);
int		exit_len(char **tab);
void	ft_exit(char **tab, t_mini_sh *mini_sh);
void	ft_exit_1(char **tab, t_mini_sh *mini_sh);
//built_in/export_simple.c
int		export(char **argv, t_mini_sh *mini_sh);
int		is_sorted(t_mini_sh *mini_sh);
int		print_export(char **argv, t_mini_sh *mini_sh);
void	sort_export(t_mini_sh *mini_sh);
void	swap_line(int i, t_mini_sh *mini_sh);
//built_in/export_utils.c
int		already_here(t_mini_sh *mini);
int		are_they_the_same(t_mini_sh *mini_sh, int i);
void	ft_free_tab(char **tab);
int		if_arg(char **argv, t_mini_sh *mini_sh);
int		init_env_sorted(t_mini_sh *mini_sh);
//built_in/is_built_in.c
int		do_built_in(t_mini_sh *mini_sh, int i);
int		init_env(t_mini_sh *mini_sh);
int		is_built_in_2(int i, t_mini_sh *mini_sh);
void	is_built_in_3(t_mini_sh *mini_sh, int i);
//built_in/cd.c
int		do_cd(int *i, char *home, char **str, t_mini_sh *mini_sh);
int		export_cd(char **str, t_mini_sh *mini_sh);
void	export_home(char *home, t_mini_sh *mini_sh);
int		ft_cd(char **str, t_mini_sh *mini_sh);
void	replace_pwd(t_mini_sh *mini_sh, int *is_exist, char *oldpwd);
//built_in/env.c
int		check_env(char **argv);
int		env(char **argv, t_mini_sh *mini_sh);
//built_in/echo.c
int		ft_echo(char **str);
//built_in/built_in_utils.c
int		export_specific(char *to_export, t_mini_sh *mini_sh);
//built_in/pwd.c
int		check_pwd_option(char **argv);
int		ft_pwd(char **argv);

#endif
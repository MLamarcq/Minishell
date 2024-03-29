/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamarcq <mlamarcq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:14:58 by gael              #+#    #+#             */
/*   Updated: 2023/05/03 11:14:05 by mlamarcq         ###   ########.fr       */
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
}			t_exec_t;

typedef struct s_env
{
	char	**env_sorted;
	char	**new_envp;
	char	*dest;
	char	*temp;
	int		size;
	int		count;
	int		ite_genv;
	char	*env_ctt;
	char	*dest_unset;
	int		len;
	int		j;
	int		i;
}			t_env;

typedef struct s_mini_sh
{
	int			count_redir_r;
	int			count_redir_l;
	int			count_hr_doc;
	int			count_append;
	int			check;
	int			redir_alone;
	int			sep_id;
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
	t_parse		*temp;
	t_parse		*tmp;
	t_parse		*tmp_2;
	t_parse		*tmp_3;
}				t_mini_sh;
// ---------------------------- end struct ---------------------------------- //

//signal/exec_signal.c
void	exec_signal(int index);
void	handle_sigint_2(int sig);
void	handle_sigint_3(int sig);
void	handle_sigquit(int sig);
//signal/handle_ctrl_c.c
void	handle_ctrl_c(int signal);
//main.c
void	init_env_2(char **envp, t_mini_sh *mini_sh);
void	init_rl(t_mini_sh *mini_sh);
void	launch_cmd(t_mini_sh *mini_sh);
//parsing/expand.c
void	exit_code(t_mini_sh *mini_sh);
void	expand(t_mini_sh *mini_sh);
int		ft_isthere_dollar(t_mini_sh *mini_sh, int *i_isdollar);
void	inside_expand(t_mini_sh *mini_sh, int *save, int *i_dollar, char *dest);
void	toggle_quote(t_mini_sh *mini_sh, char chr);
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
void	all_move(t_mini_sh *mini_sh);
int		move_1(t_mini_sh *mini_sh);
int		move_2(t_mini_sh *mini_sh);
void	move_2_3(t_mini_sh *mini, t_parse *tmp, t_parse *temp, t_parse *tmp_2);
int		move_3(t_mini_sh *mini_sh);
//parsing/is_sep_parsing.c
int		is_all(int type);
int		issep_read(int type);
int		issep_write(int type);
//parsing/move_rdr_utils.c
void	move_last(t_mini_sh *mini, t_parse *temp, t_parse *tmp, t_parse *tmp_3);
void	move_middle(t_mini_sh *mini_sh);
//parsing/glue_redirl.c
void	detect_redirl_glue(t_mini_sh *mini_sh, int *is_did, int *glue, int ite);
void	detect_redirl_glue_2(t_mini_sh *mini, int *is_did, int *glue, int ite);
void	glue_redirl(t_mini_sh *mini_sh);
void	in_glue_redirl(t_mini_sh *mini_sh, int *ite, int *is_did, int *glue);
void	set_after_glue_redirl(t_mini_sh *mini_sh, int glue);
//parsing/move_rdr_case.c
int		case_1(t_mini_sh *mini_sh);
int		case_2(t_mini_sh *mini_sh);
int		case_3(t_mini_sh *mini_sh);
//parsing/glue_pipe.c
void	detect_space_glue(t_mini_sh *mini_sh, int *is_did, int *glue, int ite);
void	glue_pipe(t_mini_sh *mini_sh);
void	set_after_glue_pipe(t_mini_sh *mini_sh, int glue);
//parsing/glue_hrdoc.c
void	detect_hrdc_glue(t_mini_sh *mini_sh, int *is_did, int *glue, int ite);
void	detect_hrdc_glue_2(t_mini_sh *mini_sh, int *is_did, int *glue, int ite);
void	glue_hrdoc(t_mini_sh *mini_sh);
void	inside_glue_hrdoc(t_mini_sh *mini_sh, int *ite, int *is_did, int *glue);
void	set_after_glue_hrdoc(t_mini_sh *mini_sh, int glue);
//parsing/remove_quote_2.c
int		isthere_quote(t_mini_sh *mini_sh);
void	remove_quote_2(t_mini_sh *mini_sh);
//parsing/replace_dollar.c
void	free_dest_expand(char **dest);
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
void	all_glue(t_mini_sh *mini_sh);
void	set_index(t_mini_sh *mini_sh);
//parsing/glue_redirr.c
void	detect_redirr_glue(t_mini_sh *mini_sh, int *is_did, int *glue, int ite);
void	detect_redirr_glue_2(t_mini_sh *mini, int *is_did, int *glue, int ite);
void	glue_redirr(t_mini_sh *mini_sh);
void	in_glue_redirr(t_mini_sh *mini_sh, int *ite, int *is_did, int *glue);
void	set_after_glue_redirr(t_mini_sh *mini_sh, int glue);
//parsing/redir_error_2.c
int		check_redir_follow(t_mini_sh *mini_sh);
int		redir_l_error(t_mini_sh *mini_sh);
int		redir_r_error_2(t_mini_sh *mini_sh);
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
void	inside_glue_app(t_mini_sh *mini_sh, int *ite, int *is_did, int *glue);
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
int		hrdoc_isthere_dollar(t_mini_sh *mini_sh, char *word, int *i_isdollar);
//exec/which_sep.c
int		init_exec(t_mini_sh *mini_sh);
void	init_exec_2(t_mini_sh *mini_sh);
//exec/rdr_start_exec.c
int		count_redir_in_line(t_mini_sh *mini_sh, int type);
int		exec_redir(t_mini_sh *mini, int i_exec);
int		first_is_a_redir(t_mini_sh *mini_sh);
void	increase_check(t_mini_sh *mini_sh, int type);
int		is_there_a_redir(t_mini_sh *mini_sh);
//exec/first_sep.c
int		check_first_is_sep(t_mini_sh *mini_sh);
int		check_first_is_sep_2(t_mini_sh *mini_sh);
int		check_first_sep_error_2(t_mini_sh *mini_sh);
//exec/redir_r.c
void	analyse_redir_before_alloc(t_mini_sh *mini_sh, t_parse **tmp);
void	change_nbr_r(t_mini_sh *mini_sh);
int		init_redir_r_tab(t_mini_sh *mini_sh);
int		middle_redir_r(t_mini_sh *mini_sh, t_parse **tmp, int i);
void	when_append_after(t_mini_sh *mini_sh, int i);
//exec/heredoc_2.c
void	child_hrdoc(t_mini_sh *mini_sh, t_parse *tmp, int i);
void	do_heredoc(t_mini_sh *mini_sh, int i, t_parse *tmp);
int		exec_all_hr_doc(t_mini_sh *mini_sh);
int		handle_input(t_mini_sh *mini_sh, t_parse *tmp, char **input);
int		middle_last_read(t_mini_sh *mini_sh, int i_last_read, int check);
//exec/exit.c
void	ft_parent(t_mini_sh *mini_sh, int *i_exec);
//exec/init_fd.c
void	count_redir_for_alloc(t_parse *tmp, t_mini_sh *mini_sh);
void	init_redir_fd(t_mini_sh *mini_sh);
//exec/tab_fd.c
int		fill_fd_tab(t_mini_sh *mini_sh, int i_init_fd, t_parse **tmp);
int		init_tab_fd(t_mini_sh *mini_sh);
int		start_to_alloc(t_mini_sh *mini_sh);
//exec/sep_test.c
void	if_hr_doc(t_mini_sh *mini_sh);
//exec/exec_utils.c
void	fill_little_tab(t_mini_sh *mini_sh, int trple);
int		init_big_tab(t_mini_sh *mini_sh);
//exec/change_nbr_utils.c
int		change_nbr_hr_util(t_mini_sh *mini_sh, t_parse *temp, int *check);
int		change_nbr_l_util(t_mini_sh *mini_sh, t_parse *temp, int *check);
int		change_nbr_r_util(t_mini_sh *mini_sh, t_parse *temp, int *check);
//exec/redir_l.c
void	analyse_redir_before_alloc_2(t_mini_sh *mini_sh, t_parse **tmp);
void	change_nbr_l(t_mini_sh *mini_sh);
int		init_redir_l_tab(t_mini_sh *mini_sh);
int		middle_redir_l(t_mini_sh *mini_sh, t_parse **tmp, int i);
int		one_hr_multi_l(t_mini_sh *mini_sh);
//exec/heredoc_4.c
void	go_to_last_read_3(t_mini_sh *mini_sh, int i_exec);
int		middle_last_read_2(t_mini_sh *mini_sh, int i_last_read, int check);
//exec/start_exec_2.c
int		execution(t_mini_sh *mini_sh, int i_exec);
int		init_sep_type(t_mini_sh *mini_sh);
int		start_exec(t_mini_sh *mini_sh);
//exec/child_process_utils.c
void	cmd_not_found(t_mini_sh *mini_sh, int i_exec);
void	end_exec_cmd(t_mini_sh *mini_sh);
void	print_cmd_not_found(t_mini_sh *mini_sh, int i_exec);
//exec/redir_l_utils.c
int		check_last_read(t_mini_sh *mini_sh, int i_last_read, int check, int i);
void	do_good_redir(t_mini_sh *mini_sh, int i_exec);
int		do_good_redir_l(t_mini_sh *mini_sh, int i_exec);
void	do_redir_l(t_mini_sh *mini_sh, int i_exec);
void	free_redir_l(t_mini_sh *mini_sh);
//exec/redir_l_utils_2.c
void	go_to_last_read_2(t_mini_sh *mini_sh, int i_exec);
void	rdr_l_hr_success(t_parse *tmp, int *hr_check);
//exec/heredoc_3.c
void	do_heredoc_redir(t_mini_sh *mini_sh, int i_exec);
void	free_hr_doc(t_mini_sh *mini_sh);
void	go_to_last_read(t_mini_sh *mini_sh, int i_exec);
void	one_l_multi_hr_util(t_parse *tmp, int *hr_check);
void	unlink_hr_dc(t_mini_sh *mini_sh);
//exec/child_process.c
void	child_process(t_mini_sh *mini_sh, int i_exec);
void	exec_cmd(t_mini_sh *mini_sh, int i_exec);
char	*ft_find_cmd_2(t_mini_sh *mini_sh, int ite_env, char *cmd_to_find);
char	*ft_find_path_2(t_mini_sh *mini_sh, char *cmd_to_find);
int		init_fd_exec(t_mini_sh *mini, int i_exec);
//exec/append.c
void	analyse_append_before_alloc(t_mini_sh *mini_sh, t_parse **tmp);
void	change_nbr_append(t_mini_sh *mini_sh);
int		init_append_tab(t_mini_sh *mini_sh);
int		init_fd_app(t_mini_sh *mini_sh, t_parse **tmp, int *i);
void	when_redir_r_after(t_mini_sh *mini_sh, int i);
//exec/sep.c
int		count_sep_2(t_mini_sh *mini_sh);
void	is_redir_alone(t_mini_sh *mini_sh);
int		is_sep(char *word);
int		is_sep_int(int type);
//exec/redir_r_utils.c
void	do_redir_r(t_mini_sh *mini_sh, int i_exec);
void	free_redir_r(t_mini_sh *mini_sh);
//exec/close.c
void	close_all(t_mini_sh *mini_sh);
void	close_pipe(t_mini_sh *mini_sh, int i);
void	close_rdr(int *tab_rdr, int nbr_rdr);
//exec/utils_append.c
int		change_nbr_append_util(t_mini_sh *mini_sh, t_parse *temp, int *check);
void	do_append(t_mini_sh *mini_sh, int i_exec);
void	free_append(t_mini_sh *mini_sh);
int		init_append_tab_util(t_mini_sh *mini_sh, t_parse **tmp, int *i);
//exec/expand_hrdoc_utils.c
void	hrdoc_replace_dollar(t_mini_sh *mini_sh, char **word, int *i_replace);
void	hrdoc_start_rplc_dlr(char **word, int *sv, int *sv2, int *i_rplc);
//exec/heredoc.c
void	analyse_hrdoc_before_alloc(t_mini_sh *mini_sh, t_parse *tmp);
void	change_hr_doc(t_mini_sh *mini_sh);
int		init_hr_dc_tab(t_mini_sh *mini_sh);
int		middle_hrdoc_tab(t_mini_sh *mini_sh, t_parse **tmp, int i);
int		one_l_multi_hr(t_mini_sh *mini_sh);
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
void	free_sep_type(t_mini_sh *mini_sh);
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
t_parse	*ft_lstnew_word(char *content, int save, int ite);
//lib/ft_lstadd_back.c
void	ft_lstadd_back(t_parse **lst, t_parse *new);
//lib/bzero.c
char	*ft_bzero(char *str, int len);
//lib/ft_strlen.c
int		ft_strlen(char *str);
//lib/ft_putstr_fd.c
void	ft_putstr_fd(char *s, int fd);
//lib/ft_memset.c
void	*ft_memset(void *s, int c, size_t len);
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
void	end_empty_line(t_mini_sh *mini_sh);
int		strcmp_empty_line(t_mini_sh *mini_sh);
int		to_empty_line_utils(t_mini_sh *mini_sh, char **argv);
//built_in/export_arg.c
int		alloc_new_tab(t_mini_sh *mini_sh);
int		export_arg(char **argv, t_mini_sh *mini_sh);
int		realloc_tab(int *i, t_mini_sh *mini_sh);
int		realloc_tab_util(t_mini_sh *mini_sh, int *check, int *i);
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
//built_in/exit_build.c
void	check_arg(t_mini_sh *mini_sh);
int		check_num(char **tab);
int		exit_len(char **tab);
void	ft_exit(char **tab, t_mini_sh *mini_sh);
void	ft_exit_1(char **tab, t_mini_sh *mini_sh);
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
int		fill_n(char *str);
int		ft_echo(char **tab);
//built_in/built_in_utils.c
int		exec_builtin(t_mini_sh *mini_sh, int i);
int		export_specific(char *to_export, t_mini_sh *mini_sh);
//built_in/pwd.c
int		check_pwd_option(char **argv);
int		ft_pwd(char **argv);

#endif
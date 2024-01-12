##### COLOR #####
BLACK = \033[1;30m
REDBG = \033[30;41m
RED = \033[0;31m
GREEN = \033[0;32m
ORANGE = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
NC = \033[0m

##### VAR #####
NAME   = minishell
CC     = gcc -Wall -Werror -Wextra -g3
# -MMD -MP

SRC  := main.c \
lib/bzero.c \
lib/envp_size.c \
lib/ft_atoi.c \
lib/ft_is_digit.c \
lib/ft_getenv.c \
lib/ft_cmp.c \
lib/ft_is_separator.c \
lib/ft_lstadd_back.c \
lib/ft_lstnew_word.c \
lib/ft_split.c \
lib/ft_strdup.c \
lib/ft_strjoin.c \
lib/ft_strlen.c \
lib/ft_itoa.c \
lib/ft_putstr_fd.c \
lib/ft_memset.c \
built_in/echo.c \
built_in/cd.c \
built_in/pwd.c \
built_in/env.c \
built_in/exit_build.c \
built_in/export_arg.c \
built_in/export_simple.c \
built_in/unset.c \
built_in/is_built_in.c \
built_in/built_in_utils.c \
built_in/empty_line_utils.c \
built_in/export_utils.c \
signal/exec_signal.c \
signal/handle_ctrl_c.c \
free/free_parsing.c \
free/free_exec.c \
free/free_env.c \
free/free_all.c \
parsing/expand.c \
parsing/parsing.c \
parsing/set_type.c \
parsing/glue_pipe.c \
parsing/glue_hrdoc.c \
parsing/glue_append.c \
parsing/glue_redirr.c \
parsing/glue_redirl.c \
parsing/is_sep_parsing.c \
parsing/replace_dollar.c \
parsing/quote.c \
parsing/remove_quote_2.c \
parsing/find_var_env.c \
parsing/ft_find_path.c \
parsing/redir_error_1.c \
parsing/redir_error_2.c \
parsing/move_rdr_cmd.c \
parsing/str_wo_qt.c \
parsing/set_type_utils.c \
parsing/set_index.c \
parsing/move_rdr_utils.c \
parsing/move_rdr_case.c \
exec/change_nbr_utils.c \
exec/prepare_exec.c \
exec/sep.c \
exec/which_sep.c \
exec/start_exec_2.c \
exec/exec_utils.c \
exec/child_process.c \
exec/heredoc.c \
exec/sep_test.c \
exec/redir_r.c \
exec/redir_l.c \
exec/append.c \
exec/init_fd.c \
exec/first_sep.c \
exec/heredoc_2.c \
exec/exit.c \
exec/expand_hrdoc.c \
exec/expand_hrdoc_utils.c \
exec/utils_append.c \
exec/close.c \
exec/child_process_utils.c \
exec/redir_l_utils.c \
exec/redir_l_utils_2.c \
exec/redir_r_utils.c \
exec/heredoc_utils.c \
exec/tab_fd.c \
exec/rdr_start_exec.c \
exec/heredoc_3.c \
exec/heredoc_4.c \

OBJ = $(SRC:%.c=%.o)
OBJS_MAEL = $(SRC_MAEL:%.c=%.o)
DEPS = $(OBJ:%.o=%.d)

OBJ_DIR := objs/
OBJ_MAEL = $(addprefix $(OBJ_DIR), ${SRC_MAEL:.c=.o})

##### RULES #####
all: $(NAME)

$(NAME) : $(OBJ)
	@echo
	@echo -e "${CYAN} ----- compile -----${NC}"
	@echo
	$(CC) $(OBJ) -lreadline -o $(NAME)

# ${OBJ_DIR}%.o : %.c

${OBJ_DIR}%.o : %.c Makefile
	$(CC) -c $< -o $@

test_mael:
	@echo
	@echo -e "${CYAN} ----- compile -----${NC}"
	@echo
	$(CC) $(OBJ_MAEL) -lreadline -o $(NAME)

clean:
	@echo
	@echo -e "${CYAN} ----- clean...  -----${NC}"
	@echo
	rm -f $(OBJ_MAEL)
	rm -f $(OBJ)
	rm -f $(DEPS)
	@echo
	@echo -e "${CYAN} ----- ✅ clean done -----${NC}"
	@echo

fclean :
	@echo
	@echo -e "${CYAN} ----- clean...  -----${NC}"
	@echo
	make clean --no-print-directory
	rm -f $(NAME)
	@echo
	@echo -e "${CYAN} ----- ✅ fclean done -----${NC}"
	@echo

re : fclean all

# -include ${DEPS}

.PHONY: clean fclean all re


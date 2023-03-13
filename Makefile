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

# SRC  :=	free/free_parsing.c \
# 		lib_gael/ft_cmp.c \
# 		lib_gael/ft_is_separator.c \
# 		lib_gael/ft_lstadd_back.c \
# 		lib_gael/ft_lstnew_word.c \
# 		lib_gael/ft_split.c \
# 		lib_gael/ft_strdup.c \
# 		lib_gael/ft_strjoin.c \
# 		lib_gael/ft_strlen.c \
# 		lib_gael/main.c \
# 		parsing/expand.c \
# 		parsing/ft_find_path.c \
# 		parsing/parsing.c \
# 		parsing/prepare_exec.c \
# 		parsing/quote.c \
# 		parsing/set_type.c

SRC  := main.c \
lib/bzero.c \
lib/envp_size.c \
lib/ft_getenv.c \
lib/ft_cmp.c \
lib/ft_is_separator.c \
lib/ft_lstadd_back.c \
lib/ft_lstnew_word.c \
lib/ft_split.c \
lib/ft_strdup.c \
lib/ft_strjoin.c \
lib/ft_strlen.c \
built_in/echo.c \
built_in/cd.c \
built_in/pwd.c \
built_in/env.c \
built_in/export_arg.c \
built_in/export_simple.c \
built_in/unset.c \
built_in/is_built_in.c \
signal/exec_signal.c \
signal/handle_ctrl_c.c \
free/free_parsing.c \
parsing/expand.c \
parsing/parsing.c \
parsing/set_type.c \
parsing/quote.c \
parsing/remove_quote.c \
parsing/ft_find_path.c \
exec/prepare_exec.c \
exec/sep.c \
exec/which_sep.c \
exec/start_exec.c \

SRC_MAEL  := main.c \
lib/ft_strncmp.c \
built_in/echo.c \
built_in/cd.c \

OBJ = $(SRC:%.c=%.o)
OBJS_MAEL = $(SRC_MAEL:%.c=%.o)
DEPS = $(OBJ:%.o=%.d)

OBJ_DIR := objs_mael/
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

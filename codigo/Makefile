# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frivas <frivas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 17:27:37 by brivera           #+#    #+#              #
#    Updated: 2025/05/23 14:28:24 by frivas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3

LIBFT_DIR := libs/libft/
LIBFT := $(LIBFT_DIR)/libft.a

INCLUDE_DIR	:= include/
SOURCES_DIR := src/
BUILT_INS_DIR := src/built_ins/
EXECUTION_DIR := src/execution/
INITIAL_DIR := src/initial/
PARCE_DIR := src/parce/
UTILS_DIR := src/utils/

SOURCES		:=	$(SOURCES_DIR)main.c
BUILT		:=	$(BUILT_INS_DIR)cd.c $(BUILT_INS_DIR)env.c \
				$(BUILT_INS_DIR)export_00.c $(BUILT_INS_DIR)export_01.c \
				$(BUILT_INS_DIR)export_02.c \
				$(BUILT_INS_DIR)unset.c $(BUILT_INS_DIR)exit.c \
				$(BUILT_INS_DIR)pwd.c $(BUILT_INS_DIR)echo.c \
				$(BUILT_INS_DIR)cd_01.c
EXECUTION	:=	$(EXECUTION_DIR)ms_execution.c $(EXECUTION_DIR)ms_redir_management.c \
				$(EXECUTION_DIR)ms_heredoc_management.c $(EXECUTION_DIR)ms_simple_execution.c \
				$(EXECUTION_DIR)ms_exec_other_onecommand.c $(EXECUTION_DIR)ms_execution_utils.c \
				$(EXECUTION_DIR)ms_pipe_management.c $(EXECUTION_DIR)ms_redir_child.c \
				$(EXECUTION_DIR)ms_move_env_to_pointer.c

INITIAL		:=	$(INITIAL_DIR)ms_get_prompt.c $(INITIAL_DIR)ms_init_struct.c \
				$(INITIAL_DIR)ms_loop_minishell.c $(INITIAL_DIR)signals.c \
				$(INITIAL_DIR)ms_loop_minishell_nointeractive.c

PARCE 		:=	$(PARCE_DIR)ms_input_row_validation.c \
				$(PARCE_DIR)ms_check_quotation_marks.c \
				$(PARCE_DIR)ms_check_pipes.c $(PARCE_DIR)ms_check_redir.c \
				$(PARCE_DIR)ms_split_input.c $(PARCE_DIR)ms_expand_variable.c \
				$(PARCE_DIR)ms_quotes_killer.c $(PARCE_DIR)ms_redir_together.c \
				$(PARCE_DIR)ms_token_input.c $(PARCE_DIR)ms_orquest.c \
				$(PARCE_DIR)ms_orquest_command.c $(PARCE_DIR)ms_expand_variable_special.c \
				$(PARCE_DIR)ms_orquest_redir.c $(PARCE_DIR)ms_control_expand_heredoc.c \
				$(PARCE_DIR)ms_block_expand_var.c $(PARCE_DIR)ms_check_redir_01.c

UTILS		:=	$(UTILS_DIR)utils.c $(UTILS_DIR)ft_isspace.c $(UTILS_DIR)ft_print_array.c \
				$(UTILS_DIR)ft_list_remove_if.c $(UTILS_DIR)ft_split_quotes.c \
				$(UTILS_DIR)ft_split_pipes.c $(UTILS_DIR)ft_list_extract_if.c \
				$(UTILS_DIR)ft_free_memory.c $(UTILS_DIR)ft_special_char.c \
				$(UTILS_DIR)ms_update_prompt.c $(UTILS_DIR)ms_get_cwd.c \
				$(UTILS_DIR)ft_print_error.c $(UTILS_DIR)ft_close_heredoc_fds.c \
				$(UTILS_DIR)ms_qd_killer.c $(UTILS_DIR)ft_free_memory_child.c \
				$(UTILS_DIR)ft_print_error_point.c

SRC 		:=	$(SOURCES) $(BUILT) $(EXECUTION) $(INITIAL) $(PARCE) $(UTILS)

OBJ_DIR 	:=	obj/
OBJ 		:=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_SUBDIRS :=	$(sort $(dir $(OBJ)))

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	LIBRARY := -L$(LIBFT_DIR) -lft -L/usr/lib -lreadline
	INCLUDE := -I/usr/include -I$(LIBFT_DIR) -I$(INCLUDE_DIR)
endif
ifeq ($(UNAME), Darwin)
	LIBRARY := -L$(LIBFT_DIR) -lft -L/usr/local/opt/readline/lib -lreadline
	INCLUDE := -I/usr/local/opt/readline/include -I$(LIBFT_DIR) -I$(INCLUDE_DIR)
endif

RED := \033[91;1m
GREEN := \033[92;1m
CLEAR_COLOR := \033[0m
CYAN := \033[96;1m

RM := rm -rf

all: $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ Compilado LIBFT\n$(CLEAR_COLOR)"

$(OBJ_SUBDIRS):
	@mkdir -p $@

$(OBJ_DIR)%.o: %.c | $(OBJ_SUBDIRS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) $(LIBRARY) $(INCLUDE) -o $(NAME)
	@echo "$(GREEN)🖥️  Compilado Minishell\n$(CLEAR_COLOR)"

clean:
	@make clean --no-print-directory -C $(LIBFT_DIR)
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)⛔ Limpieza de archivos objeto\n$(CLEAR_COLOR)"
	
fclean: clean
	@$(RM) $(NAME)
	@make fclean clean --no-print-directory -C $(LIBFT_DIR)
	@echo "$(RED)⛔ Limpieza total (ejecutables y librerías)\n$(CLEAR_COLOR)"
		
re: fclean all
	@echo "$(CYAN)🔃 Proyecto reconstruido\n$(CLEAR_COLOR)"

valgrind:
	valgrind -s \
		--tool=memcheck \
		--leak-check=full \
		--show-leak-kinds=all \
		--show-reachable=yes \
		--track-origins=yes \
		--trace-children=yes \
		--track-fds=yes \
		--suppressions=valgrind/valgrind.sup \
		--log-file=valgrind/informe \
		./$(NAME)

norminette:
	@norminette $(SOURCES) $(BUILT) $(EXECUTION) $(INITIAL) $(PARCE) $(UTILS) $(INCLUDE_DIR)

.PHONY: valgrind clean fclean re norminette

.DEFAULT_GOAL := all

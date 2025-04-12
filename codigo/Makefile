# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frivas <frivas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 17:27:37 by brivera           #+#    #+#              #
#    Updated: 2025/04/12 15:47:25 by frivas           ###   ########.fr        #
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
				$(BUILT_INS_DIR)unset.c $(BUILT_INS_DIR)exit.c \
				$(BUILT_INS_DIR)pwd.c
EXECUTION	:=	$(EXECUTION_DIR)ms_execution.c
INITIAL		:=	$(INITIAL_DIR)ms_get_prompt.c $(INITIAL_DIR)ms_init_struct.c \
				$(INITIAL_DIR)ms_loop_minishell.c $(INITIAL_DIR)signals.c 

PARCE 		:=	$(PARCE_DIR)ms_input_row_validation.c \
				$(PARCE_DIR)ms_check_quotation_marks.c \
				$(PARCE_DIR)ms_check_pipes.c $(PARCE_DIR)ms_check_redir.c \
				$(PARCE_DIR)ms_split_input.c $(PARCE_DIR)ms_expand_variable.c

UTILS		:=	$(UTILS_DIR)utils.c $(UTILS_DIR)ft_isspace.c $(UTILS_DIR)ft_print_array.c \
				$(UTILS_DIR)ft_list_remove_if.c \
				$(UTILS_DIR)ft_split_quotes.c $(UTILS_DIR)ft_split_pipes.c

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

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ Compilado LIBFT\n$(CLEAR_COLOR)"

$(OBJ_SUBDIRS):
	@mkdir -p $@

$(OBJ_DIR)%.o: %.c | $(OBJ_SUBDIRS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) $(LIBRARY) $(INCLUDE) -o $(NAME)
	@echo "$(GREEN)✅ Compilada la Minishell\n$(CLEAR_COLOR)"


clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)⛔ Limpieza de archivos objeto.$(CLEAR_COLOR)"
	
fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)⛔ Limpieza total (ejecutables y librerías).$(CLEAR_COLOR)"
		
re: fclean all
	@echo "$(CYAN)🔃 Proyecto reconstruido$(CLEAR_COLOR)"

valgrind:
	valgrind -s \
		--tool=memcheck \
		--leak-check=full \
		--show-leak-kinds=all \
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

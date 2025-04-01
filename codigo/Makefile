# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frivas <frivas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 17:27:37 by brivera           #+#    #+#              #
#    Updated: 2025/04/01 15:52:12 by frivas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

OBJ_DIR := obj/

INCLUDE_DIR = include/

LIBFT_DIR = ./libs/libft/

SOURCES_DIR = src/
BUILT_INS_DIR = src/built_ins/
EXECUTION_DIR = src/execution/
INITIAL_DIR = src/initial/
PARCE_DIR = src/parce/
UTILS_DIR = src/utils/

SOURCES = $(SOURCES_DIR)main.c

BUILT = $(BUILT_INS_DIR)cd.c

EXECUTION = 

INITIAL = $(INITIAL_DIR)ms_get_prompt.c $(INITIAL_DIR)ms_init_struct.c $(INITIAL_DIR)ms_loop_minishell.c \
				$(INITIAL_DIR)signals.c

PARCE =

UTILS = $(UTILS_DIR)utils.c

SRC := $(SOURCES) $(BUILT) $(EXECUTION) $(INITIAL) $(PARCE) $(UTILS)

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	LIBRARY := -L$(LIBFT_DIR) -lft -L/usr/lib -lreadline
	INCLUDE := -I/usr/include -I$(LIBFT_DIR) -I$(INCLUDE_DIR)
endif

ifeq ($(UNAME), Darwin)
	LIBRARY := -L$(LIBFT_DIR) -lft -L/usr/local/opt/readline/lib -lreadline
	INCLUDE := -I/usr/local/opt/readline/include -I$(LIBFT_DIR) -I$(NCLUDE_DIR)
endif

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3
RM = rm -f

OBJ_SUBDIRS = $(OBJ_DIR)$(SOURCES) $(OBJ_DIR)$(BUILT) $(OBJ_DIR)$(EXECUTION) $(OBJ_DIR)$(INITIAL) \
	$(OBJ_DIR)$(PARCE) $(OBJ_DIR)$(UTILS)


.DEFAULT_GOAL := all

all: libft $(NAME)

libft:
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ Compilado LIBFT\n$(CLEAR_COLOR)"

$(OBJ_SUBDIRS):
	@mkdir -p $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_SUBDIRS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	@$(CC) $(OBJ) $(LIBRARY) $(INCLUDE) -o $(NAME)
	@echo "$(GREEN)✅ Compilada la Minishell\n$(CLEAR_COLOR)"

RED := \033[91;1m
GREEN := \033[92;1m
CLEAR_COLOR := \033[0m
CYAN := \033[96;1m

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)⛔ Limpieza de archivos objeto.$(CLEAR_COLOR)"
	
fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)⛔ Limpieza total (ejecutables y librerías).$(CLEAR_COLOR)"
		
re: fclean all
	@echo "$(CYAN)🔃 Proyecto reconstruido.$(CLEAR_COLOR)"

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
	@norminette $(SRC) $(INCLUDE)

.PHONY: valgrind clean fclean re norminette

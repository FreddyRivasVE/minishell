# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 17:27:37 by brivera           #+#    #+#              #
#    Updated: 2025/03/24 16:23:33 by brivera          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

LIBFT_DIR = libs/libft
LIBFTA = $(LIBFT_DIR)/libft.a

LIBS = -lreadline -Llib/libft

UNAME = $(shell uname)
ifeq ($(UNAME), linux)
	LIBS = -Llib/libft -lft -L/Users/$(USER)/.brew/opt/readline/lib -lreadline
	INCLUDE = -I/Users/$(USER)/.brew/opt/readline/include -I include
endif

SRC_DIR = src
SRCS = 	$(SRC_DIR)/main.c $(SRC_DIR)/ms_init_struct.c $(SRC_DIR)/signals.c

OBJ_DIR = obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDE = include/minishell.h

RED = \033[91;1m
GREEN = \033[92;1m
CLEAR_COLOR = \033[0m
CYAN = \033[96;1mc
RM = rm -f

all: $(NAME)

$(NAME): $(LIBFTA) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFTA) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✅ Compilada la Minishell\n$(CLEAR_COLOR)"

$(LIBFTA):
	@make -C $(LIBFT_DIR)
	@make -C $(LIBFT_DIR) bonus
	@echo "$(GREEN)✅ Compilado LIBFT\n$(CLEAR_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -Iinclude -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)⛔ Limpieza de archivos objeto.$(CLEAR_COLOR)"

fclean: clean
	@$(RM) $(NAME)
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
	@norminette $(SRCS) $(INCLUDE)

.PHONY: valgrind clean fclean re norminette

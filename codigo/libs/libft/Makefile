# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makeoutfile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 11:36:05 by brivera           #+#    #+#              #
#    Updated: 2024/12/17 15:29:53 by brivera          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./

SRC_DIR = src/ft
OBJ_DIR = obj
BONUS_SRC_DIR = src/bonus
OBJ_BONUS_DIR = src/bonus
# Archivos fuente y objetos
SRC = $(SRC_DIR)/ft_isalpha.c $(SRC_DIR)/ft_isdigit.c $(SRC_DIR)/ft_isalnum.c \
      $(SRC_DIR)/ft_isascii.c $(SRC_DIR)/ft_isprint.c $(SRC_DIR)/ft_strlen.c \
      $(SRC_DIR)/ft_memset.c $(SRC_DIR)/ft_bzero.c $(SRC_DIR)/ft_memcpy.c \
      $(SRC_DIR)/ft_memmove.c $(SRC_DIR)/ft_strlcpy.c $(SRC_DIR)/ft_strlcat.c \
      $(SRC_DIR)/ft_toupper.c $(SRC_DIR)/ft_tolower.c $(SRC_DIR)/ft_strchr.c \
      $(SRC_DIR)/ft_strrchr.c $(SRC_DIR)/ft_strncmp.c $(SRC_DIR)/ft_memchr.c \
      $(SRC_DIR)/ft_memcmp.c $(SRC_DIR)/ft_strnstr.c $(SRC_DIR)/ft_atoi.c \
      $(SRC_DIR)/ft_calloc.c $(SRC_DIR)/ft_strdup.c $(SRC_DIR)/ft_substr.c \
      $(SRC_DIR)/ft_strjoin.c $(SRC_DIR)/ft_strtrim.c $(SRC_DIR)/ft_split.c \
      $(SRC_DIR)/ft_itoa.c $(SRC_DIR)/ft_strmapi.c $(SRC_DIR)/ft_striteri.c \
      $(SRC_DIR)/ft_putchar_fd.c $(SRC_DIR)/ft_putstr_fd.c $(SRC_DIR)/ft_putendl_fd.c \
	$(SRC_DIR)/ft_putnbr_fd.c \
	$(SRC_DIR)/get_next_line.c

BONUS_SRC = $(BONUS_SRC_DIR)/ft_lstnew_bonus.c $(BONUS_SRC_DIR)/ft_lstadd_front_bonus.c \
            $(BONUS_SRC_DIR)/ft_lstsize_bonus.c $(BONUS_SRC_DIR)/ft_lstlast_bonus.c \
            $(BONUS_SRC_DIR)/ft_lstadd_back_bonus.c $(BONUS_SRC_DIR)/ft_lstdelone_bonus.c \
            $(BONUS_SRC_DIR)/ft_lstclear_bonus.c $(BONUS_SRC_DIR)/ft_lstiter_bonus.c \
            $(BONUS_SRC_DIR)/ft_lstmap_bonus.c

OBJ = $(OBJ_DIR)/ft_isalpha.o $(OBJ_DIR)/ft_isdigit.o $(OBJ_DIR)/ft_isalnum.o \
      $(OBJ_DIR)/ft_isascii.o $(OBJ_DIR)/ft_isprint.o $(OBJ_DIR)/ft_strlen.o \
      $(OBJ_DIR)/ft_memset.o $(OBJ_DIR)/ft_bzero.o $(OBJ_DIR)/ft_memcpy.o \
      $(OBJ_DIR)/ft_memmove.o $(OBJ_DIR)/ft_strlcpy.o $(OBJ_DIR)/ft_strlcat.o \
      $(OBJ_DIR)/ft_toupper.o $(OBJ_DIR)/ft_tolower.o $(OBJ_DIR)/ft_strchr.o \
      $(OBJ_DIR)/ft_strrchr.o $(OBJ_DIR)/ft_strncmp.o $(OBJ_DIR)/ft_memchr.o \
      $(OBJ_DIR)/ft_memcmp.o $(OBJ_DIR)/ft_strnstr.o $(OBJ_DIR)/ft_atoi.o \
      $(OBJ_DIR)/ft_calloc.o $(OBJ_DIR)/ft_strdup.o $(OBJ_DIR)/ft_substr.o \
      $(OBJ_DIR)/ft_strjoin.o $(OBJ_DIR)/ft_strtrim.o $(OBJ_DIR)/ft_split.o \
      $(OBJ_DIR)/ft_itoa.o $(OBJ_DIR)/ft_strmapi.o $(OBJ_DIR)/ft_striteri.o \
      $(OBJ_DIR)/ft_putchar_fd.o $(OBJ_DIR)/ft_putstr_fd.o $(OBJ_DIR)/ft_putendl_fd.o \
      $(OBJ_DIR)/ft_putnbr_fd.o \
      $(OBJ_DIR)/get_next_line.o

BONUS_OBJ = $(OBJ_BONUS_DIR)/ft_lstnew_bonus.o $(OBJ_BONUS_DIR)/ft_lstadd_front_bonus.o \
            $(OBJ_BONUS_DIR)/ft_lstsize_bonus.o $(OBJ_BONUS_DIR)/ft_lstlast_bonus.o \
            $(OBJ_BONUS_DIR)/ft_lstadd_back_bonus.o $(OBJ_BONUS_DIR)/ft_lstdelone_bonus.o \
            $(OBJ_BONUS_DIR)/ft_lstclear_bonus.o $(OBJ_BONUS_DIR)/ft_lstiter_bonus.o \
            $(OBJ_BONUS_DIR)/ft_lstmap_bonus.o

INCLUDE = libft.h

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
#	@echo "\nLibrería $(NAME) compilada."

bonus: $(OBJ) 
	@make -s SRC="$(SRC) $(BONUS_SRC)" OBJ="$(OBJ) $(BONUS_OBJ)" 
#	@echo "Librería con bonus compilada."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR) 
	@$(CC) $(CFLAGS) -c $< -o $@ 
	@echo -n "\rCompilando: $<"

$(OBJ_DIR)/bonus/%.o: $(BONUS_SRC_DIR)/%.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)/bonus
	@echo "Compilando: $< \r"
#	@echo "Compilando archivo bonus:\r $<"

clean:
	@rm -rf $(OBJ_DIR) 
#@echo "Archivos objeto eliminados."

fclean: clean
	@rm -f $(NAME)
#@echo "Librería eliminada."

re: fclean all

.PHONY: all bonus clean fclean re


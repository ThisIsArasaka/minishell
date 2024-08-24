# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 15:31:23 by olardeux          #+#    #+#              #
#    Updated: 2024/08/24 14:49:22 by olardeux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f
SRC = main.c parsing.c utils.c read_file.c free.c special_char.c
INC_SRC = minishell.h
LIBFT = libft/libft.a
LIBFT_DIR = libft/
SRCDIR = src/
INCDIR = inc/
OBJDIR = obj/
OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))
INC = $(addprefix $(INCDIR), $(INC_SRC))

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INC)
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@
	@echo "$< Compiled"

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@echo "Minishell Compiled"

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJ)
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFT_DIR)
	@echo "Minishell Object Files Removed"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "Minishell Removed"

re: fclean all

.PHONY: all clean fclean re


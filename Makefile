# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 04:08:54 by olardeux          #+#    #+#              #
#    Updated: 2024/11/05 07:31:20 by olardeux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f
SRC_FILE = check_replace.c error.c main.c quote.c special_char.c \
			env.c free.c parsing.c read_file.c token.c signals.c \
			env_init.c quote_check.c 
BULTINS_FILE = ft_echo.c ft_pwd.c ft_exit.c ft_export.c ft_unset.c ft_env.c \
				ft_cd.c builtins.c
UTILS_FILE = parsing_utils.c token_utils.c cmd_utils.c
SRC_DIR = src
BULTINS_DIR = src/builtins
UTILS_DIR = src/utils
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILE)) $(addprefix $(BULTINS_DIR)/, $(BULTINS_FILE)) $(addprefix $(UTILS_DIR)/, $(UTILS_FILE))
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILE:.c=.o) $(BULTINS_FILE:.c=.o)) $(addprefix $(OBJ_DIR)/, $(UTILS_FILE:.c=.o))
INC = -I./inc
LIBFT = libft/libft.a

all: $(NAME)

$(LIBFT):
	@make -s -C libft
	@echo "\033[0;34mLibft compiled!\033[0m"

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo "\033[0;34mMiniShell compiled!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "\033[0;32mCompilation of \033[0;33m$< \033[0;32mdone.\033[0m"

$(OBJ_DIR)/%.o: $(BULTINS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "\033[0;32mCompilation of \033[0;33m$< \033[0;32mdone.\033[0m"

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "\033[0;32mCompilation of \033[0;33m$< \033[0;32mdone.\033[0m"

clean:
	@make -s clean -C libft
	@$(RM) -r $(OBJ_DIR)
	@echo "\033[0;31mObjects removed.\033[0m"

fclean: clean
	@make -s fclean -C libft
	@$(RM) $(NAME)
	@echo "\033[0;31m$(NAME) removed.\033[0m"

re: fclean all
	@echo "\033[0;34m$(NAME) recompiled!\033[0m"

.PHONY: all clean fclean re
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:37:52 by olardeux          #+#    #+#             */
/*   Updated: 2024/09/19 23:34:53 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define FILE_READ_BUFFER_SIZE 1024

# define PROMPT "minishell\033[0;34m$\033[0m "

typedef struct s_parsing
{
	int					i;
	int					args_count;
	char				**tokens;
}						t_parsing;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_cmd_list
{
	char				*cmd;
	char				**args;
	char				*output;
	int					append;
	struct s_cmd_list	*next;
}						t_cmd_list;

char					*read_file(char *filename);

t_cmd_list				*parsing(char **line, t_env *env);

t_env					*init_env(char **envp);

int						redirect_input(t_cmd_list *cmd, t_parsing *parsing,
							int start, int arg_num);
int						redirect_output(t_cmd_list *cmd, t_parsing *parsing,
							int start);
int						redirect_append(t_cmd_list *cmd, t_parsing *parsing,
							int start);

char					**add_quote_token(char **tokens, char *line,
							int token_count, int *i);

char					**token_copy(char **tokens, int token_count);
char					**token_split(char *line);
int						tokens_count(char **tokens, char sep_end);

char					*ft_add_char_pos(char *str, char c, int pos);
int						ft_isblank(char c);
char					*ft_add_char(char *str, char c);
int						is_special_char(char c);

void					free_cmd_list(t_cmd_list *cmd_list);
void					free_tokens(char **tokens);
void					free_env(t_env *env);

#endif
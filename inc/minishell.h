/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:37:52 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/27 11:14:25 by olardeux         ###   ########.fr       */
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

typedef struct s_cmd_list
{
	char				*cmd;
	char				**args;
	char				*output;
	int					append;
	struct s_cmd_list	*next;
}						t_cmd_list;

int						ft_isblank(char c);
int						tokens_count(char **tokens, char sep_end);
char					last_char(char *str);
char					*read_file(char *filename);
t_cmd_list				*parsing(char **line);
void					free_cmd_list(t_cmd_list *cmd_list);
void					free_tokens(char **tokens);
int						redirect_input(t_cmd_list *cmd, char **tokens,
							int start, int arg_num);
int						redirect_output(t_cmd_list *cmd, char **tokens,
							int start);
char					**quote_split(char *line);
int						quote_span(char **token, char sign);
char					*adjust_line(char *line);
char					*ft_add_char_pos(char *str, char c, int pos);
char					*ft_add_char(char *str, char c);
int						quote_in_token(char *token);

#endif
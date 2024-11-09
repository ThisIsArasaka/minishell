/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:37:52 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/09 22:40:06 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "parsing.h"
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

# define MALLOC_ERROR "malloc error"
# define SYNTAX_ERROR "syntax error"
# define NO_FILE "No such file or directory"
# define NO_PERM "Permission denied"
# define NO_CMD "command not found"
# define ENV_INIT_FAIL "env initialization failed"
# define HOME_NOT_SET "HOME not set"
# define CD_ERROR "cd error"

# ifndef FILE_READ_BUFFER_SIZE
#  define FILE_READ_BUFFER_SIZE 1024
# endif

# define PROMPT "minishell\033[0;34m$\033[0m "

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
	char				*input;
	int					append;
	struct s_cmd_list	*next;
}						t_cmd_list;

typedef struct s_data
{
	t_cmd_list			*cmd_list;
	t_env				*env;
	char				*line;
}						t_data;

// int						g_status;

char					*read_file(char *filename);

t_env					*init_env(char **envp);
char					*get_env_value(t_env *env, char *name);
char					*get_env_exec(t_env *env, char *name);
char					**env_to_array(t_env *env);
t_env					*param_env(char *env);

int						ft_isblank(char c);
char					*ft_add_char(char *str, char c);
int						is_special_char(char c);

void					free_cmd_list(t_cmd_list *cmd_list);
void					free_tokens(t_token *tokens);
void					free_tab(char **tab);
void					free_env(t_env *env);

void					error_msg(char *msg, char *arg);

void					signal_init(void);

int						is_builtin(t_cmd_list *cmd);
int						builtin(t_data *data);

int						name_match(char *name, char *arg);

int						ft_echo(t_cmd_list *cmd);
int						ft_pwd(void);
int						ft_exit(t_data *data);
int						ft_export(t_cmd_list *cmd, t_env *env);
int						ft_unset(t_cmd_list *cmd, t_env *env);
int						ft_env(t_env *env);
int						ft_cd(t_cmd_list *cmd, t_env *env);

#endif
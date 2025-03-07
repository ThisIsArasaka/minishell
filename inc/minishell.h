/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marida-c <marida-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:37:52 by olardeux          #+#    #+#             */
/*   Updated: 2024/12/02 15:43:27 by marida-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include "parsing.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
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
# define CD_ERROR "minishell: cd"
# define EXPORT_ERROR "export : not a valid identifier"

# ifndef FILE_READ_BUFFER_SIZE
#  define FILE_READ_BUFFER_SIZE 1024
# endif

# define PROMPT "minishell\033[0;34m$\033[0m "

# define OUTPUT 1
# define APPEND 2
# define INPUT 3

# define RED "\033[1;31m"
# define RESET "\033[0m"

extern int				g_sig;

typedef struct s_env
{
	char				*name;
	char				*value;
	char				*env_list;
	bool				isunset;
	struct s_env		*next;

}						t_env;

typedef struct s_redir
{
	char				*file;
	int					fd;
	int					type;
	struct s_redir		*next;
}						t_redir;

typedef struct s_cmd_list
{
	char				*cmd;
	char				**args;
	char				*cmd_path;

	struct s_redir		*redir;
	struct s_cmd_list	*next;
	struct s_cmd_list	*prev;

}						t_cmd_list;

typedef struct s_data
{
	t_cmd_list			*cmd_list;
	t_env				*env;
	char				*line;
	int					excode;
	int					tmpexcode;
}						t_data;

typedef struct s_fd
{
	int					pipes[2];
	int					redir[2];
	int					input;
	int					output;
}						t_fd;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
				BUILTINS
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

// bultins-launcher

int			is_builtin(t_cmd_list *cmd);
int			builtin(t_data *data, t_cmd_list *cmd);

// builtins

int			ft_echo(t_cmd_list *cmd);
int			ft_pwd(t_data *data, t_cmd_list *cmd);
int			ft_exit(t_data *data, t_cmd_list *cmd);
int			ft_export(t_cmd_list *cmd, t_data *data);
int			ft_unset(t_cmd_list *cmd, t_env **env);
int			ft_env(t_env *env);
int			ft_cd(t_cmd_list *cmd, t_data *data);

int			name_match(char *name, char *arg);

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
				ENV
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

// env_init.c
t_env		*init_env(char **envp);
int			add_to_array(char **array, t_env *env, int i);
char		**env_to_array(t_env *env);

// env.c
t_env		*param_env(char *env);
char		*get_env_value(t_env *env, char *name);
char		*add_cmd_path(char *path, char *cmd);
char		*get_env_exec(t_env *env, char *name);

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
				EXEC
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

// exec.c
void		init_fds_and_redirections(t_cmd_list *current_cmd, t_fd *fds,
				t_data *data);
void		execute_process(t_data *data, t_cmd_list *current_cmd, t_fd *fds);
void		exec_bultin(t_data *data, t_fd *fds, t_cmd_list *cmd);
void		execute_child(t_data *data, t_cmd_list *cmd, t_fd *fds);
void		exec(t_data *data);

// exec_utils.c
void		free_envp(char **envp);
void		exec_cmd(t_data *data, t_cmd_list *cmd, char **envp);
int			is_builtin_command(t_data *data, t_cmd_list *cmd);

// fds.c
void		init_fds(t_fd *fds);
void		set_fds(t_fd *fd);
void		close_all_fds(t_fd *fds);
void		close_fds_parent(t_fd *fds);
void		wait_child(t_data *data);

// heredoc.c
void		loop_here_doc(char *delimiter, int fd, t_data *data);
int			handle_heredoc(char *delimiter, t_data *data);

// redir.c
void		apply_redirections(t_cmd_list *cmd, int *fd_in, int *fd_out,
				t_data *data);
int			handle_input_redir(t_redir *redir, int fd_in, t_data *data);
int			handle_output_redir(t_redir *redir, int fd_out, t_data *data);

// utils

int			ft_isblank(char c);
char		*ft_add_char(char *str, char c);
int			is_special_char(char c);
void		exit_free(t_data *data);

// token

void		free_cmd_list(t_cmd_list *cmd_list);
void		free_tokens(t_token *tokens);
void		free_tab(char **tab);
void		free_env(t_env *env);
void		free_redir(t_redir *redir);

// error

void		error_msg(char *msg, char *arg);

// signal

void		init_sig(void);
void		init_sig_heredoc(void);

#endif
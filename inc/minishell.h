/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:37:52 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/29 10:17:52 by olardeux         ###   ########.fr       */
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
# include <stdbool.h>
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
# define CD_ERROR "cd : no such file or directory"
# define EXPORT_ERROR "export : not a valid identifier"

# ifndef FILE_READ_BUFFER_SIZE
#  define FILE_READ_BUFFER_SIZE 1024
# endif

# define PROMPT "minishell\033[0;34m$\033[0m "

# define OUTPUT 1
# define APPEND 2
# define INPUT 3

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
	int saved_stdin;  // Ajout pour sauvegarder STDIN
	int saved_stdout; // Ajout pour sauvegarder STDOUT

}						t_fd;

# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define RESET "\033[0m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[1;96m"
# define ITALIC "\033[3m"

// char **get_paths_from_env();
// int handle_redirections(t_cmd_list *cmd_list);
// void cleanup_exec(char **envp, char *cmd_path);
// int count_cmds(t_cmd_list *cmd_list);
// int **init_pipes(int num_cmds);
// void close_pipes(int **pipe_fds, int num_cmds);
// void exec_builtin(t_cmd_list *cmd, int **pipe_fds, int i, int num_cmds,
// t_data *data);
// void exec_external(t_cmd_list *cmd, int **pipe_fds, int i, int num_cmds,
// t_data *data);
// void exec(t_data *data);
// int handle_redirections(t_cmd_list *cmd);
// void exec_cmd(t_cmd_list *cmd_list, t_env *env);

char	*find_cmd_path(t_data *data, char *cmd); //
void					exec(t_data *data);
void					exec_bultin(t_data *data, t_fd *fds, t_cmd_list *cmd);
void					exec_cmd(t_data *data, t_cmd_list *cmd, char **envp);

int						handle_heredoc(char *delimiter, t_data *data);
void					loop_here_doc(char *delimiter, int fd, t_data *data);
void					apply_redirections(t_cmd_list *cmd, int *fd_in,
							int *fd_out, t_data *data);
// void				run_builtins(t_cmd_list *cmd, t_fd *fds);
void	child_builtins(t_fd *fds);                                         //
void	execute_child(t_data *data, t_cmd_list *cmd, t_fd *fds);           //
char	**get_paths_from_env(t_env *env);                                  //
void	execute_process(t_data *data, t_cmd_list *current_cmd, t_fd *fds); //
// int					handle_builtins(t_cmd_list *current_cmd);
void	init_fds_and_redirections(t_cmd_list *current_cmd, t_fd *fds,
								t_data *data); //
// int					is_builtin_command(const char *command);
int	is_dir(const char *path);                                              //
char	*get_cmd_path(t_data *data, t_cmd_list *cmd, t_fd *fds, char **envp); //
void	free_envp(char **envp);                                               //
void	redirect_input_output(t_fd *fds);                                     //
void	setup_pipes(t_fd *fds);                                               //
void	close_fds_parent(t_fd *fds);                                          //

void	init_fds(t_fd *fds);         //
void	set_fds(t_fd *fd);           //
void	close_all_fds(t_fd *fds);    //
void	close_fds_parent(t_fd *fds); //
void					wait_child(t_data *data);

void					ft_free_split(char **split);
char					*strjoin_free(char *s1, char *s2);
void					init_data(t_data *data);

int						count_env_entries(t_env *env_list);

void					print_cmd_list(t_cmd_list *cmd_list);
void					restore_fds(t_fd *fd);

char					*read_file(char *filename);

// env

t_env					*init_env(char **envp);
char					*get_env_value(t_env *env, char *name);
char					*get_env_exec(t_env *env, char *name);
char					**env_to_array(t_env *env);
t_env					*param_env(char *env);

// utils

int						ft_isblank(char c);
char					*ft_add_char(char *str, char c);
int						is_special_char(char c);
void					exit_free(t_data *data);

// token

void					free_cmd_list(t_cmd_list *cmd_list);
void					free_tokens(t_token *tokens);
void					free_tab(char **tab);
void					free_env(t_env *env);
void					free_redir(t_redir *redir);

// error

void					error_msg(char *msg, char *arg);

// signal

void					init_sig(void);
void					init_sig_heredoc(void);

// bultins-launcher

int						is_builtin(t_cmd_list *cmd);
int						builtin(t_data *data, t_cmd_list *cmd);

// builtins

int						ft_echo(t_cmd_list *cmd);
int						ft_pwd(t_data *data, t_cmd_list *cmd);
int						ft_exit(t_data *data, t_cmd_list *cmd);
int						ft_export(t_cmd_list *cmd, t_data *data);
int						ft_unset(t_cmd_list *cmd, t_env *env);
int						ft_env(t_env *env);
int						ft_cd(t_cmd_list *cmd, t_data *data);

int						name_match(char *name, char *arg);

#endif
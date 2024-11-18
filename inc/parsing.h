/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 22:37:10 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/16 15:54:48 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_cmd_list	t_cmd_list;
typedef struct s_env		t_env;
typedef struct s_redir		t_redir;

enum						e_token
{
	WORD,
	INPUT,   // <
	OUTPUT,  // >
	APPEND,  // >>
	HEREDOC, // <<
	PIPE,    // |
	ERROR    // error
};

typedef struct s_token
{
	char					*token;
	enum e_token			type;
	struct s_token			*next;
}							t_token;

typedef struct s_parsing
{
	int						i;
	int						args_count;
	int						token_start;
	int						token_count;
	struct s_token			*tokens;
	struct s_env			*env;
}							t_parsing;

t_cmd_list					*parsing(char **line, t_env *env);

int							init_cmd_list(t_cmd_list **cmd_list,
								t_token *tokens);
int							get_command(t_cmd_list *cmd, t_parsing *parsing,
								t_token *start);
int							detect_token(t_cmd_list *cmd, t_parsing *parsing,
								t_token **start, int *j);
int							set_redir(t_redir *redir, t_cmd_list *cmd,
								t_token *start);

t_redir						*init_redir(void);
int							redirect_input(t_cmd_list *cmd, t_parsing *parsing,
								t_token **start);
int							redirect_output(t_cmd_list *cmd, t_parsing *parsing,
								t_token **start);
int							redirect_append(t_cmd_list *cmd, t_parsing *parsing,
								t_token **start);

t_token						*add_quote_token(t_token *tokens, char *line,
								int *i);
int							quote_count_init(char *line, int *pos);

t_token						*add_new_token(t_token *tokens);
t_token						*add_token(t_parsing *parsing, char *line,
								int token_len);
int							add_quote_char(char *line, t_parsing *parsing);
int							last_token(char *line, t_parsing *parsing);
int							add_special_char(char *line, t_parsing *parsing);
t_token						*token_split(char *line);
int							tokens_count(t_token *tokens);

char						*check(char *line, t_env *env);
char						*replace_var(char *line, int place, t_env *env);
int							in_quote(char *line, int place);
void						add_var(int *i, int *j, char *var, char *new);
void						add_var_quoted(int *i, int *j, char *var,
								char *new);
void						skip_var_name(char *line, int *i);

void						skip_quote(char *line, int *i);
int							check_quote(char *line);

#endif
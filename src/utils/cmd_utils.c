/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marida-c <marida-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 06:29:34 by olardeux          #+#    #+#             */
/*   Updated: 2024/12/02 16:23:37 by marida-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cmd_list(t_cmd_list **cmd_list, t_token *tokens)
{
	int	args_count;

	args_count = tokens_count(tokens);
	if (args_count < 0)
		return (error_msg(SYNTAX_ERROR, NULL), 0);
	*cmd_list = malloc(sizeof(t_cmd_list));
	if (!*cmd_list)
		return (error_msg(MALLOC_ERROR, NULL), 0);
	(*cmd_list)->args = malloc(sizeof(char *) * (args_count + 1));
	if (!(*cmd_list)->args)
		return (free((*cmd_list)), error_msg(MALLOC_ERROR, NULL), 0);
	(*cmd_list)->cmd = NULL;
	(*cmd_list)->args[0] = NULL;
	(*cmd_list)->redir = NULL;
	(*cmd_list)->next = NULL;
	return (1);
}

int	get_command(t_cmd_list *cmd, t_parsing *parsing, t_token **start)
{
	if ((*start)->type == PIPE)
		return (error_msg(SYNTAX_ERROR, 0), 0);
	else if ((*start)->type == INPUT || (*start)->type == OUTPUT
		|| (*start)->type == APPEND || (*start)->type == HEREDOC)
	{
		if ((*start)->token[0] == '>')
		{
			if (!redirect_output(cmd, parsing, start))
				return (0);
		}
		else if ((*start)->token[0] == '<')
		{
			if (!redirect_input(cmd, parsing, start))
				return (0);
		}
	}
	else
	{
		cmd->cmd = ft_strdup((*start)->token);
		if (!cmd->cmd)
			return (error_msg(MALLOC_ERROR, NULL), 0);
		parsing->i++;
	}
	return (1);
}

int	detect_token(t_cmd_list *cmd, t_parsing *parsing, t_token **start, int *j)
{
	if ((*start)->type == INPUT || (*start)->type == OUTPUT
		|| (*start)->type == APPEND || (*start)->type == HEREDOC)
	{
		if ((*start)->token[0] == '>')
		{
			if (!redirect_output(cmd, parsing, start))
				return (cmd->args[*j] = NULL, 0);
		}
		else if ((*start)->token[0] == '<')
		{
			if (!redirect_input(cmd, parsing, start))
				return (cmd->args[*j] = NULL, 0);
		}
	}
	else
	{
		cmd->args[*j] = ft_strdup((*start)->token);
		if (!cmd->args[*j])
			return (error_msg(MALLOC_ERROR, NULL), 0);
		parsing->i++;
		(*start) = (*start)->next;
		(*j)++;
	}
	return (1);
}

int	set_redir(t_redir *redir, t_cmd_list *cmd, t_token *start)
{
	t_redir	*tmp;

	if (!redir)
		return (0);
	redir->file = ft_strdup(start->next->token);
	if (!redir->file)
		return (error_msg(MALLOC_ERROR, NULL), 0);
	if (start->type == INPUT)
		redir->type = INPUT;
	else if (start->type == OUTPUT)
		redir->type = OUTPUT;
	else if (start->type == APPEND)
		redir->type = APPEND;
	else if (start->type == HEREDOC)
		redir->type = HEREDOC;
	if (!cmd->redir)
		cmd->redir = redir;
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
	return (1);
}

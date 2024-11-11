/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 06:29:34 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/11 12:04:38 by olardeux         ###   ########.fr       */
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
	(*cmd_list)->input = NULL;
	(*cmd_list)->output = NULL;
	(*cmd_list)->next = NULL;
	(*cmd_list)->append = 0;
	return (1);
}

int	get_command(t_cmd_list *cmd, t_parsing *parsing, t_token *start)
{
	if (start->type == PIPE)
		return (error_msg(SYNTAX_ERROR, 0), 0);
	else if (start->type == INPUT || start->type == OUTPUT
		|| start->type == APPEND || start->type == HEREDOC)
	{
		if (start->token[0] == '>')
		{
			if (!redirect_output(cmd, parsing, &start))
				return (0);
		}
		else if (start->token[0] == '<')
		{
			if (!redirect_input(cmd, parsing, &start))
				return (0);
		}
	}
	else
	{
		cmd->cmd = ft_strdup(start->token);
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
		cmd->args[*j] = ft_strdup((*start)->token);
		if (!cmd->args[*j])
			return (error_msg(MALLOC_ERROR, NULL), 0);
		parsing->i++;
		(*start) = (*start)->next;
		(*j)++;
	}
	return (1);
}

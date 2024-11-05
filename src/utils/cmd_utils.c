/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 06:29:34 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/05 07:16:28 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cmd_list(t_cmd_list **cmd_list, char **tokens)
{
	int	args_count;

	args_count = tokens_count(tokens, '|');
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

int	get_command(t_cmd_list *cmd, t_parsing *parsing, int start)
{
	if (is_special_char(parsing->tokens[start][0])
		&& (parsing->tokens[start][1] == '\0'
			|| (is_special_char(parsing->tokens[start][1])
				&& parsing->tokens[start][2] == '\0')))
	{
		if (parsing->tokens[start][0] == '>')
		{
			if (!redirect_output(cmd, parsing, start))
				return (0);
		}
		else if (parsing->tokens[start][0] == '<')
		{
			if (!redirect_input(cmd, parsing, start, 0))
				return (0);
		}
	}
	cmd->cmd = get_env_exec(parsing->env, parsing->tokens[start + parsing->i]);
	if (!cmd->cmd)
		return (error_msg(MALLOC_ERROR, NULL), 0);
	return (1);
}

int	detect_token(t_cmd_list *cmd, t_parsing *parsing, int start, int *j)
{
	if (is_special_char(parsing->tokens[start + parsing->i][0])
		&& (parsing->tokens[start + parsing->i][1] == '\0'
			|| (is_special_char(parsing->tokens[start + parsing->i][1])
				&& parsing->tokens[start + parsing->i][2] == '\0')))
	{
		if (parsing->tokens[start + parsing->i][0] == '>')
		{
			if (!redirect_output(cmd, parsing, start + parsing->i))
				return (0);
		}
		else if (parsing->tokens[start + parsing->i][0] == '<')
		{
			if (!redirect_input(cmd, parsing, start + parsing->i, *j))
				return (0);
		}
	}
	else
	{
		cmd->args[*j] = ft_strdup(parsing->tokens[start + parsing->i]);
		if (!cmd->args[*j])
			return (error_msg(MALLOC_ERROR, NULL), 0);
		parsing->i++;
		(*j)++;
	}
	return (1);
}

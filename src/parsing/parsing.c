/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:13:15 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/29 00:07:34 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_cmd(t_cmd_list *cmd, t_parsing *parsing, t_token *start,
		t_data *data)
{
	int	j;

	j = 0;
	parsing->i = 0;
	if (!start)
		return (data->excode = 1, error_msg(SYNTAX_ERROR, NULL), 0);
	if (!get_command(cmd, parsing, start))
		return (0);
	while (start && start->type != PIPE)
	{
		if (!detect_token(cmd, parsing, &start, &j))
			return (data->excode = 1, 0);
	}
	cmd->args[j] = NULL;
	return (1);
}

t_cmd_list	*token_to_command(t_parsing *parsing, t_data *data)
{
	t_token		*tmp;
	t_cmd_list	*cmd_list;
	t_cmd_list	*current;

	tmp = parsing->tokens;
	if (!init_cmd_list(&cmd_list, tmp))
		return (NULL);
	current = cmd_list;
	if (!create_cmd(current, parsing, tmp, data))
		return (free_cmd_list(cmd_list), NULL);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!init_cmd_list(&current->next, tmp->next))
				return (free_cmd_list(cmd_list), NULL);
			current = current->next;
			if (!create_cmd(current, parsing, tmp->next, data))
				return (free_cmd_list(cmd_list), NULL);
		}
		tmp = tmp->next;
	}
	return (cmd_list);
}

t_cmd_list	*parsing(t_data *data)
{
	t_parsing	parsing;
	t_cmd_list	*cmd_list;

	parsing.env = data->env;
	data->line = check(data->line, data);
	if (!data->line)
		return (NULL);
	parsing.tokens = token_split(data->line);
	if (!parsing.tokens)
		return (NULL);
	cmd_list = token_to_command(&parsing, data);
	if (!cmd_list)
		return (free_tokens(parsing.tokens), NULL);
	free_tokens(parsing.tokens);
	return (cmd_list);
}

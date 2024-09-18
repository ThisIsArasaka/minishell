/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:13:15 by olardeux          #+#    #+#             */
/*   Updated: 2024/09/18 11:33:22 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cmd_list(t_cmd_list **cmd_list, char **tokens)
{
	int	args_count;

	args_count = tokens_count(tokens, '|');
	printf("tokens_count = %d\n", args_count);
	*cmd_list = malloc(sizeof(t_cmd_list));
	if (!*cmd_list)
		return (0);
	(*cmd_list)->args = malloc(sizeof(char *) * (args_count + 1));
	if (!(*cmd_list)->args)
		return (free((*cmd_list)), 0);
	(*cmd_list)->cmd = NULL;
	(*cmd_list)->args[0] = NULL;
	(*cmd_list)->output = NULL;
	(*cmd_list)->next = NULL;
	(*cmd_list)->append = 0;
	return (1);
}

int	create_cmd(t_cmd_list *cmd, t_parsing *parsing, int start)
{
	int	j;

	j = 0;
	parsing->i = 0;
	cmd->cmd = ft_strdup(parsing->tokens[start]);
	if (!cmd->cmd)
		return (0);
	while (parsing->tokens[start + parsing->i] && parsing->tokens[start
		+ parsing->i][0] != '|')
	{
		if (parsing->tokens[start + parsing->i][0] == '<')
		{
			if (!redirect_input(cmd, parsing, start + parsing->i, j))
				return (0);
			j++;
		}
		else if (parsing->tokens[start + parsing->i][0] == '>')
		{
			if (parsing->tokens[start + parsing->i][1] == '>')
			{
				if (!redirect_append(cmd, parsing, start + parsing->i))
					return (0);
			}
			else
			{
				if (!redirect_output(cmd, parsing, start + parsing->i))
					return (0);
			}
		}
		else
		{
			cmd->args[j] = ft_strdup(parsing->tokens[start + parsing->i]);
			if (!cmd->args[j])
				return (0);
			parsing->i++;
			j++;
		}
	}
	cmd->args[j] = NULL;
	return (1);
}

t_cmd_list	*token_to_command(t_parsing *parsing)
{
	int			i;
	int			last;
	t_cmd_list	*cmd_list;
	t_cmd_list	*current;

	i = 0;
	last = 0;
	parsing->quote_count = 0;
	if (!init_cmd_list(&current, parsing->tokens))
		return (NULL);
	cmd_list = current;
	if (!create_cmd(current, parsing, last))
		return (free_cmd_list(cmd_list), NULL);
	while (parsing->tokens[i])
	{
		if (ft_strncmp(parsing->tokens[i], "|", 2) == 0)
		{
			if (!init_cmd_list(&current->next, parsing->tokens + i + 1))
				return (free_cmd_list(cmd_list), NULL);
			current = current->next;
			last = i + 1;
			if (!create_cmd(current, parsing, last))
				return (free_cmd_list(cmd_list), NULL);
		}
		i++;
	}
	return (cmd_list);
}

t_cmd_list	*parsing(char **line)
{
	t_parsing	parsing;
	t_cmd_list	*cmd_list;

	parsing.tokens = token_split(*line);
	if (!parsing.tokens)
		return (NULL);
	cmd_list = token_to_command(&parsing);
	if (!cmd_list)
		return (free_tokens(parsing.tokens), NULL);
	free_tokens(parsing.tokens);
	return (cmd_list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:13:15 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/24 15:38:00 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cmd_list(t_cmd_list **cmd_list, char **tokens)
{
	int	args_count;

	args_count = tokens_count(tokens, '|');
	*cmd_list = malloc(sizeof(t_cmd_list));
	if (!*cmd_list)
		return (0);
	(*cmd_list)->args = malloc(sizeof(char *) * (args_count + 2));
	if (!(*cmd_list)->args)
		return (free((*cmd_list)), 0);
	(*cmd_list)->cmd = NULL;
	(*cmd_list)->args[0] = NULL;
	(*cmd_list)->output = NULL;
	(*cmd_list)->next = NULL;
	(*cmd_list)->append = 0;
	return (1);
}

int	create_cmd(t_cmd_list *cmd, char **tokens, int start)
{
	int	i;
	int	j;
	int	inquote;

	i = 0;
	j = 0;
	inquote = 0;
	cmd->cmd = ft_strdup(tokens[start]);
	if (!cmd->cmd)
		return (0);
	while (tokens[start + i] && tokens[start + i][0] != '|')
	{
		if (!inquote && tokens[start + i][0] == '<')
		{
			if (!redirect_input(cmd, tokens, start + i, j))
				return (0);
			i += 2;
			j++;
		}
		else if (!inquote && tokens[start + i][0] == '>')
		{
			if (!redirect_output(cmd, tokens, start + i))
				return (0);
			i += 2;
			j++;
		}
		else if (!inquote && tokens[start + i][0] == '"')
		{
			if (!inquote_parsing(cmd, tokens, start + i, j))
				return (0);
			inquote = 1;
		}
		else if (inquote && last_char(tokens[start + i]) == '"')
			inquote = 0;
		else
		{
			cmd->args[j] = ft_strdup(tokens[start + i]);
			if (!cmd->args[j])
				return (0);
			i++;
			j++;
		}
	}
	cmd->args[j] = NULL;
	return (1);
}

t_cmd_list	*token_to_command(char **tokens)
{
	int			i;
	int			last;
	t_cmd_list	*cmd_list;
	t_cmd_list	*current;

	i = 0;
	last = 0;
	if (!init_cmd_list(&current, tokens))
		return (NULL);
	cmd_list = current;
	if (!create_cmd(current, tokens, last))
		return (NULL);
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 2) == 0)
		{
			if (!init_cmd_list(&current->next, tokens + i + 1))
				return (free_cmd_list(cmd_list), NULL);
			current = current->next;
			last = i + 1;
			create_cmd(current, tokens, last);
		}
		i++;
	}
	return (cmd_list);
}

t_cmd_list	*parsing(char *line)
{
	char		**tokens;
	t_cmd_list	*cmd_list;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (NULL);
	cmd_list = token_to_command(tokens);
	if (!cmd_list)
		return (free_tokens(tokens), NULL);
	free_tokens(tokens);
	return (cmd_list);
}

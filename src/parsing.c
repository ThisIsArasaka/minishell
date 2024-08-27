/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:13:15 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/27 11:24:28 by olardeux         ###   ########.fr       */
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

int	create_cmd(t_cmd_list *cmd, char **tokens, int start, char **quote,
		int *quote_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!quote_in_token(tokens[start]))
	{
		cmd->cmd = ft_strdup(tokens[start]);
		if (!cmd->cmd)
			return (0);
	}
	else
	{
		cmd->cmd = ft_strdup(quote[*quote_count]);
		if (!cmd->cmd)
			return (0);
		cmd->args[0] = ft_strdup(quote[*quote_count]);
		if (!cmd->args[j])
			return (0);
		(*quote_count)++;
		i += quote_span(tokens + i, tokens[start][0]);
		j++;
	}
	while (tokens[start + i] && tokens[start + i][0] != '|')
	{
		if (tokens[start + i][0] == '<')
		{
			if (redirect_input(cmd, tokens, start + i, j))
				i += 2;
			j++;
		}
		else if (tokens[start + i][0] == '>')
		{
			if (!redirect_output(cmd, tokens, start + i))
				return (0);
			i += 2;
		}
		else if (quote_in_token(tokens[start + i]))
		{
			cmd->args[j] = ft_strdup(quote[*quote_count]);
			if (!cmd->args[j])
				return (0);
			(*quote_count)++;
			i += quote_span(tokens + (start + i), tokens[start + i][0]);
			j++;
		}
		else
		{
			cmd->args[j] = ft_strdup(tokens[start + i]);
			if (!cmd->args[j])
				return (0);
			i++;
			j++;
		}
	}
	printf("j = %d\n", j);
	cmd->args[j] = NULL;
	return (1);
}

t_cmd_list	*token_to_command(char **tokens, char **quote)
{
	int			i;
	int			quote_count;
	int			last;
	t_cmd_list	*cmd_list;
	t_cmd_list	*current;

	i = 0;
	last = 0;
	quote_count = 0;
	if (!init_cmd_list(&current, tokens))
		return (NULL);
	cmd_list = current;
	if (!create_cmd(current, tokens, last, quote, &quote_count))
		return (NULL);
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 2) == 0)
		{
			if (!init_cmd_list(&current->next, tokens + i + 1))
				return (free_cmd_list(cmd_list), NULL);
			current = current->next;
			last = i + 1;
			if (!create_cmd(current, tokens, last, quote, &quote_count))
				return (free_cmd_list(cmd_list), NULL);
		}
		i++;
	}
	return (cmd_list);
}

t_cmd_list	*parsing(char **line)
{
	char		**tokens;
	char		**quote;
	t_cmd_list	*cmd_list;

	quote = quote_split(*line);
	*line = adjust_line(*line);
	if (!line)
		return (free_tokens(quote), NULL);
	tokens = ft_split(*line, ' ');
	if (!tokens)
		return (free_tokens(quote), NULL);
	cmd_list = token_to_command(tokens, quote);
	if (!cmd_list)
		return (free_tokens(tokens), NULL);
	free_tokens(tokens);
	if (quote)
		free_tokens(quote);
	return (cmd_list);
}

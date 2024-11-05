/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:13:15 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/05 07:17:36 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_cmd(t_cmd_list *cmd, t_parsing *parsing, int start)
{
	int	j;

	j = 0;
	parsing->i = 0;
	if (!get_command(cmd, parsing, start))
		return (0);
	while (parsing->tokens[start + parsing->i]
		&& parsing->tokens[start + parsing->i][0] != '|')
	{
		if (!detect_token(cmd, parsing, start, &j))
			return (0);
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
	if (!init_cmd_list(&cmd_list, parsing->tokens))
		return (NULL);
	current = cmd_list;
	if (!create_cmd(current, parsing, 0))
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

t_cmd_list	*parsing(char **line, t_env *env)
{
	t_parsing	parsing;
	t_cmd_list	*cmd_list;

	parsing.env = env;
	*line = check_replace(*line, env);
	if (!*line)
		return (NULL);
	parsing.tokens = token_split(*line);
	if (!parsing.tokens)
		return (NULL);
	cmd_list = token_to_command(&parsing);
	if (!cmd_list)
		return (free_tokens(parsing.tokens), NULL);
	free_tokens(parsing.tokens);
	return (cmd_list);
}

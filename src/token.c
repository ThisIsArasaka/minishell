/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:53:32 by olardeux          #+#    #+#             */
/*   Updated: 2024/09/06 13:23:53 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*adjust_line(char *line)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_strdup(line);
	if (!new)
		return (NULL);
	while (new[i])
	{
		if (new[i] == '<' || new[i] == '>' || new[i] == '|')
		{
			if (i > 0 && new[i - 1] != ' ')
				new = ft_add_char_pos(new, ' ', i++);
			if (new[i + 1] && new[i + 1] != ' ')
				new = ft_add_char_pos(new, ' ', i + 1);
		}
		i++;
	}
	free(line);
	return (new);
}

int	tokens_count(char **token, char sep_end)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i] && token[i][0] != sep_end)
	{
		if (token[i][0] == '"' || token[i][0] == '\'')
		{
			i += quote_span(token + i, token[i][0]);
			printf("i = %d\n", i);
			count++;
		}
		else if (token[i][0] == '>')
			i += 2;
		else if (token[i][0] == '<')
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	**add_token(char **tokens, char *line, int start, int last)
{
	int		i;
	char	**new;

	i = 0;
	while (tokens[i])
		i++;
	new = (char **)malloc(i + 2 * sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		new[i] = ft_strdup(tokens[i]);
		if (!new[i])
		{
			free_tokens(new);
			return (NULL);
		}
		new[i + 1] = NULL;
		i++;
	}
	while (start != last)
	{
		new[i] = ft_add_char(new, line[start]);
		start++;
	}
	new[i + 1] = NULL;
	return (new);
}

char	**token_split(char *line)
{
	int		i;
	int		token_start;
	char	**split;

	i = 0;
	split = NULL;
	token_start = 0;
	while (line[i])
	{
		if (ft_isblank(line[i]))
		token_start = 
	}
}

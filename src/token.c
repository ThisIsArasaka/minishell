/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:53:32 by olardeux          #+#    #+#             */
/*   Updated: 2024/09/11 00:06:38 by olardeux         ###   ########.fr       */
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
		// if (token[i][0] == '"' || token[i][0] == '\'')
		// {
		// 	i += quote_span(token + i, token[i][0]);
		// 	printf("i = %d\n", i);
		// 	count++;
		// }
		if (token[i][0] == '>')
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

char	**add_quote_token(char **tokens, char *line, int token_count, int *i)
{
	char	**new;
	char	quote;
	int		quote_count;
	int		j;

	j = 0;
	quote_count = 0;
	new = malloc(sizeof(char *) * (token_count + 2));
	if (!new)
		return (NULL);
	while (j < token_count)
	{
		new[j] = ft_strdup(tokens[j]);
		if (!new[j])
			return (NULL);
		j++;
	}
	new[token_count] = NULL;
	j = 0;
	while (line[j] && ft_isblank(line[j]))
		j++;
	while (line[j] && !ft_isblank(line[j]) && line[j] != '<' && line[j] != '>'
		&& line[j] != '|')
	{
		if (line[j] == '"' || line[j] == '\'')
		{
			quote = line[j];
			while (line[j] && line[j] == quote)
			{
				quote_count++;
				j++;
			}
			while (line[j] && quote_count > 0)
			{
				if (line[j] == quote)
				{
					quote_count--;
					j++;
				}
				else
				{
					new[token_count] = ft_add_char(new[token_count], line[j]);
					j++;
				}
			}
		}
		else
		{
			new[token_count] = ft_add_char(new[token_count], line[j]);
			j++;
		}
	}
	*i += j - 1;
	new[token_count + 1] = NULL;
	if (tokens)
		free(tokens);
	return (new);
}

char	**add_token(char **tokens, char *line, int tokens_count, int token_len)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (tokens_count + 2));
	if (!new)
		return (NULL);
	while (i < tokens_count)
	{
		new[i] = ft_strdup(tokens[i]);
		i++;
	}
	while (line[j] && ft_isblank(line[j]))
	{
		j++;
		token_len--;
	}
	new[i] = ft_substr(line, j, token_len);
	new[i + 1] = NULL;
	if (tokens)
		free(tokens);
	return (new);
}

char	**token_split(char *line)
{
	int		i;
	int		token_start;
	int		token_count;
	char	**tokens;

	i = 0;
	tokens = NULL;
	token_start = 0;
	token_count = 0;
	while (line[i])
	{
		if (ft_isblank(line[i]) && i > 0 && !ft_isblank(line[i - 1]))
		{
			tokens = add_token(tokens, line + token_start, token_count, i
					- token_start);
			token_start = i;
			token_count++;
		}
		else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			if (i > 0 && !ft_isblank(line[i - 1]))
			{
				tokens = add_token(tokens, line + token_start, token_count, i
						- token_start);
				token_count++;
			}
			tokens = add_token(tokens, line + i, token_count, 1);
			token_count++;
			token_start = i + 1;
			i++;
		}
		else if (line[i] == '"' || line[i] == '\'')
		{
			tokens = add_quote_token(tokens, line + token_start, token_count,
					&i);
			token_count++;
			token_start = i;
		}
		printf("line[%d] = %c\n", i, line[i]);
		i++;
	}
	printf("i = %d\n", i);
	if (i > 0 && !ft_isblank(line[i - 1]) && line[i - 1] != '\'' && line[i
		- 1] != '"')
	{
		tokens = add_token(tokens, line + token_start, token_count, i
				- token_start);
		token_count++;
	}
	for (i = 0; tokens[i]; i++)
		printf("tokens[%d] = %s\n", i, tokens[i]);
	return (tokens);
}

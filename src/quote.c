/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:49:33 by olardeux          #+#    #+#             */
/*   Updated: 2024/10/14 07:41:28 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_count_init(char *line, int *pos)
{
	int		quote_count;
	char	quote;

	quote_count = 0;
	quote = line[*pos];
	while (line[*pos] && line[*pos] == quote)
	{
		quote_count++;
		(*pos)++;
	}
	if (quote_count % 2 == 0)
		return (0);
	return (quote_count);
}

int	in_quote_copy(char **new, char *line, int token_count, int *pos)
{
	int		quote_count;
	char	quote;

	quote_count = 0;
	quote = line[*pos];
	quote_count = quote_count_init(line, pos);
	if (quote_count == 0)
		return (new[token_count] = ft_add_char(new[token_count], '\0'), 1);
	while (line[*pos] && quote_count > 0)
	{
		if (line[*pos] == quote)
		{
			(*pos)++;
			break ;
		}
		else
		{
			new[token_count] = ft_add_char(new[token_count], line[*pos]);
			if (!new[token_count])
				return (0);
			(*pos)++;
		}
	}
	return (1);
}

int	add_quote(char **new, char *line, int token_count, int *pos)
{
	if (line[*pos] == '"' || line[*pos] == '\'')
	{
		if (!in_quote_copy(new, line, token_count, pos))
			return (0);
	}
	else
	{
		new[token_count] = ft_add_char(new[token_count], line[*pos]);
		if (!new[token_count])
			return (0);
		(*pos)++;
	}
	return (1);
}

char	**add_quote_token(char **tokens, char *line, int token_count, int *i)
{
	char	**new;
	int		j;

	j = 0;
	new = token_copy(tokens, token_count);
	if (!new)
		return (NULL);
	while (line[j] && ft_isblank(line[j]))
		j++;
	while (line[j] && !ft_isblank(line[j]) && line[j] != '<' && line[j] != '>'
		&& line[j] != '|')
	{
		if (!add_quote(new, line, token_count, &j))
			return (free_tokens(new), NULL);
	}
	*i += j;
	new[token_count + 1] = NULL;
	if (tokens)
		free_tokens(tokens);
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:53:32 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/08 10:07:58 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_special_char(char *line, t_parsing *parsing)
{
	if (parsing->i > 0 && !ft_isblank(line[parsing->i - 1]))
	{
		parsing->tokens = add_token(parsing, line + parsing->token_start,
				parsing->i - parsing->token_start);
		if (!parsing->tokens)
			return (0);
		(parsing->token_count)++;
	}
	if (is_special_char(line[parsing->i + 1]))
	{
		parsing->tokens = add_token(parsing, line + parsing->i, 2);
		if (!parsing->tokens)
			return (0);
		(parsing->i) += 2;
	}
	else
	{
		parsing->tokens = add_token(parsing, line + parsing->i, 1);
		if (!parsing->tokens)
			return (0);
		(parsing->i)++;
	}
	return ((parsing->token_count)++, parsing->token_start = parsing->i, 1);
}

int	add_quote_char(char *line, t_parsing *parsing)
{
	parsing->i = parsing->token_start;
	parsing->tokens = add_quote_token(parsing->tokens, line
			+ parsing->token_start, &parsing->i);
	if (!parsing->tokens)
		return (0);
	(parsing->token_count)++;
	parsing->token_start = parsing->i;
	return (1);
}

int	last_token(char *line, t_parsing *parsing)
{
	int	j;

	j = 0;
	if (parsing->i > 0 && !ft_isblank(line[parsing->i - 1]))
	{
		while ((parsing->i - j) > 0 && !ft_isblank(line[parsing->i - j - 1]))
		{
			if (line[parsing->i - j] == '\'' || line[parsing->i - j] == '"')
				return (1);
			j++;
		}
		parsing->tokens = add_token(parsing, line + parsing->token_start,
				parsing->i - parsing->token_start);
		if (!parsing->tokens)
			return (0);
		(parsing->token_count)++;
	}
	return (1);
}

int	token_type(t_parsing *parsing, char *line)
{
	if (ft_isblank(line[parsing->i]) && parsing->i > 0
		&& !ft_isblank(line[parsing->i - 1]))
	{
		parsing->tokens = add_token(parsing, line + parsing->token_start,
				parsing->i - parsing->token_start);
		parsing->token_start = parsing->i;
		(parsing->token_count)++;
	}
	if (is_special_char(line[parsing->i]))
	{
		if (!add_special_char(line, parsing))
			return (0);
	}
	if (line[parsing->i] == '"' || line[parsing->i] == '\'')
	{
		if (!add_quote_char(line, parsing))
			return (0);
	}
	return (1);
}

t_token	*token_split(char *line)
{
	t_parsing	parsing;

	parsing.i = 0;
	parsing.tokens = NULL;
	parsing.token_start = 0;
	parsing.token_count = 0;
	while (line[parsing.i])
	{
		if (!token_type(&parsing, line))
			return (NULL);
		if (line[parsing.i])
			parsing.i++;
	}
	if (!last_token(line, &parsing))
		return (parsing.tokens);
	return (parsing.tokens);
}

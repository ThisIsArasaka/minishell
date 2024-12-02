/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marida-c <marida-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:15:38 by olardeux          #+#    #+#             */
/*   Updated: 2024/12/02 16:34:25 by marida-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_special_char(char *line, t_parsing *parsing)
{
	if (parsing->i > 0 && !ft_isblank(line[parsing->i - 1])
		&& parsing->token_start < parsing->i)
	{
		parsing->tokens = add_token(parsing, line + parsing->token_start,
				parsing->i - parsing->token_start);
		if (!parsing->tokens)
			return (0);
		(parsing->token_count)++;
	}
	if (is_special_char(line[parsing->i + 1]) && line[parsing->i] != '|')
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
	if (parsing->i > 0 && !ft_isblank(line[parsing->i - 1])
		&& parsing->token_start < parsing->i)
	{
		while (line[parsing->token_start + j]
			&& !ft_isblank(line[parsing->token_start + j]))
		{
			if (line[parsing->token_start + j] == '"'
				|| line[parsing->token_start + j] == '\'')
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

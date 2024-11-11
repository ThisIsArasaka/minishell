/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:53:32 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/11 11:58:25 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_check(char *line, t_parsing *parsing)
{
	int	i;

	i = parsing->i;
	while (line[i] && !isblank(line[i]))
	{
		if (line[i] == '"' || line[i] == '\'' || is_special_char(line[i]))
			return (parsing->i++, 1);
		i++;
	}
	parsing->tokens = add_token(parsing, line + parsing->i, i - parsing->i);
	parsing->token_start = i;
	(parsing->token_count)++;
	(parsing->i) = i;
	return (1);
}

int	token_type(t_parsing *parsing, char *line)
{
	if (is_special_char(line[parsing->i]))
	{
		if (!add_special_char(line, parsing))
			return (0);
	}
	else if (line[parsing->i] == '"' || line[parsing->i] == '\'')
	{
		if (!add_quote_char(line, parsing))
			return (0);
		if (isblank(line[parsing->i]))
			(parsing->i)++;
	}
	else if (!ft_isblank(line[parsing->i]))
	{
		if (!token_check(line, parsing))
			return (0);
	}
	else if (line[parsing->i])
		parsing->i++;
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
	}
	if (!last_token(line, &parsing))
		return (parsing.tokens);
	return (parsing.tokens);
}

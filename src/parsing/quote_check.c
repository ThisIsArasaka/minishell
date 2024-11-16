/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:02:22 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/16 15:41:32 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(char *line, int *i, char quote)
{
	int	quote_count;

	quote_count = quote_count_init(line, i);
	while (line[*i] && quote_count > 0)
	{
		if (line[*i] == quote)
		{
			quote_count--;
			(*i)++;
		}
		else
			(*i)++;
	}
	return (quote_count);
}

int	check_quote(char *line)
{
	int		i;
	int		quote_count;
	char	quote;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			quote = line[i];
			quote_count = handle_quotes(line, &i, quote);
			if (quote_count % 2 != 0)
				return (error_msg(SYNTAX_ERROR, NULL), 0);
		}
		else
			i++;
	}
	return (1);
}

void	skip_quote(char *line, int *i)
{
	char	quote;
	int		quote_count;

	quote = line[*i];
	quote_count = 0;
	while (line[*i] && line[*i] == quote)
	{
		quote_count++;
		(*i)++;
	}
	while (line[*i] && quote_count > 0)
	{
		if (line[*i] == quote)
		{
			quote_count--;
			(*i)++;
		}
		else
			(*i)++;
	}
	(*i)--;
}

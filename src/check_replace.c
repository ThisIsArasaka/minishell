/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:23:44 by olardeux          #+#    #+#             */
/*   Updated: 2024/09/19 09:44:20 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *line)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			quote_count++;
		i++;
	}
	if (quote_count % 2 != 0)
		return (0);
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
}

int	check_replace(char *line, t_env *env)
{
	int	i;

	i = 0;
	(void)env;
	if (!check_quote(line))
		return (0);
	while (line[i])
	{
		if (line[i] == '\'')
			skip_quote(line, &i);
	}
	return (1);
}

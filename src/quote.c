/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:49:33 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/27 11:31:58 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_counter(char *line)
{
	int		counter;
	int		quote_counter;
	char	sign;
	int		i;

	i = 0;
	counter = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			sign = line[i];
			counter++;
			quote_counter = 0;
			while (line[i] == sign)
			{
				quote_counter++;
				i++;
			}
			while (line[i] && quote_counter)
			{
				if (line[i] == sign)
					quote_counter--;
				i++;
			}
			if (quote_counter != 0)
				return (0);
		}
		else
			i++;
	}
	return (counter);
}

int	quote_dup(char *str, char **dup, char sign)
{
	int	i;
	int	quote_counter;

	i = 0;
	quote_counter = 0;
	while (str[i] && str[i] != sign && str[i] != ' ')
	{
		*dup = ft_add_char(*dup, str[i]);
		if (!(*dup))
			return (0);
		i++;
	}
	while (str[i] == sign)
	{
		quote_counter++;
		i++;
	}
	while (str[i] && quote_counter)
	{
		if (str[i] == sign)
			quote_counter--;
		else
		{
			*dup = ft_add_char(*dup, str[i]);
			if (!(*dup))
				return (0);
		}
		i++;
	}
	if (quote_counter != 0)
		return (0);
	if (str[i] != 0 && str[i] != ' ')
		i += quote_dup(str + i, dup, sign);
	return (i);
}
char	**quote_split(char *line)
{
	char	**quote_split;
	int		counter;
	char	sign;
	int		i;
	int		j;

	i = 0;
	j = 0;
	counter = quote_counter(line);
	if (!counter)
		return (NULL);
	quote_split = malloc(sizeof(char *) * (counter + 1));
	if (!quote_split)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			if (i != 0 && line[i - 1] != ' ')
			{
				sign = line[i];
				while (i != 0 && (line[i - 1] != ' ' || line[i - 1] == '<'
						|| line[i - 1] == '>' || line[i - 1] == '|'))
					i--;
				quote_split[j] = ft_strdup(" ");
				i += quote_dup(line + i, &quote_split[j], sign);
				if (!quote_split[j])
					return (NULL);
			}
			else
			{
				quote_split[j] = ft_strdup("");
				i += quote_dup(line + i, &quote_split[j], line[i]);
				if (!quote_split[j])
					return (NULL);
			}
			j++;
		}
		else
			i++;
	}
	quote_split[j] = NULL;
	return (quote_split);
}

int	quote_span(char **tokens, char sign)
{
	int	i;
	int	j;
	int	quote_count;

	i = 0;
	j = 0;
	quote_count = 0;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j] == sign)
		{
			quote_count++;
			j++;
		}
		if (tokens[i][j] != 0)
			break ;
		i++;
	}
	while (tokens[i] && quote_count)
	{
		if (quote_in_token(tokens[i]))
		{
			j = 0;
			while (tokens[i][j] == sign)
			{
				quote_count--;
				j++;
			}
		}
		i++;
	}
	printf("span = %d\n", i);
	return (i);
}

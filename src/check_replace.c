/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:23:44 by olardeux          #+#    #+#             */
/*   Updated: 2024/10/14 07:22:17 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *line)
{
	int		i;
	int		quote_count;
	char	quote;

	i = 0;
	quote_count = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			quote = line[i];
			quote_count = quote_count_init(line, &i);
			while (line[i] && quote_count > 0)
			{
				if (line[i] == quote)
				{
					quote_count--;
					i++;
				}
				else
					i++;
			}
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

char	*replace_var(char *line, int place, t_env *env)
{
	int		i;
	int		j;
	char	*new;
	char	*var;

	i = 0;
	j = 0;
	var = get_env_value(env, line + place + 1);
	if (!var)
		var = "";
	new = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(var)));
	if (!new)
		return (error_msg(MALLOC_ERROR, NULL), free(line), NULL);
	while (line[i])
	{
		if (i == place)
		{
			while (*var)
			{
				new[j] = *var;
				var++;
				j++;
			}
			i++;
			while (line[i] && !ft_isblank(line[i]) && !is_special_char(line[i])
				&& line[i] != '"' && line[i] != '\\' && line[i] != '$'
				&& line[i] != '=' && line[i] != '/')
				i++;
		}
		new[j] = line[i];
		i++;
		j++;
	}
	new[j] = 0;
	return (free(line), new);
}

char	*check_replace(char *line, t_env *env)
{
	int	i;

	i = 0;
	if (!check_quote(line))
		return (free(line), NULL);
	while (line[i])
	{
		if (line[i] == '\'')
			skip_quote(line, &i);
		if (line[i] == '$' && !ft_isblank(line[i + 1]))
		{
			line = replace_var(line, i, env);
			if (!line)
				return (NULL);
		}
		i++;
	}
	return (line);
}

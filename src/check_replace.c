/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:23:44 by olardeux          #+#    #+#             */
/*   Updated: 2024/09/24 12:50:50 by olardeux         ###   ########.fr       */
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

char	*replace_var(char *line, int place, t_env *env)
{
	int		i;
	int		j;
	char	*new;
	char	*var;

	i = 0;
	j = 0;
	var = get_env_value(env, line + place + 1);
	printf("var: %s\nvar len: %lu", var, ft_strlen(var));
	if (!var)
		return (line);
	new = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(var)));
	if (!new)
		return (line);
	while (line[i])
	{
		if (i == place)
		{
			while (var[j])
			{
				new[i + j] = var[j];
				j++;
			}
			while (line[i] && !ft_isblank(line[i]) && !is_special_char(line[i]))
				line++;
		}
		new[i + j] = line[i];
		printf("line[%d + %d]: %c\n", i, j, line[i]);
		i++;
	}
	new[i + j] = '\0';
	return (free(line), new);
}

char	*check_replace(char *line, t_env *env)
{
	int	i;

	i = 0;
	if (!check_quote(line))
		return (NULL);
	printf("line: %s\n", line);
	while (line[i])
	{
		if (line[i] == '\'')
			skip_quote(line, &i);
		if (line[i] == '$' && !ft_isblank(line[i + 1]))
		{
			line = replace_var(line, i, env);
			if (!line)
				return (NULL);
			printf("line: %s\n", line);
		}
		i++;
	}
	return (line);
}

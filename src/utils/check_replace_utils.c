/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_replace_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:50:48 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/25 07:03:52 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_quote(char *line, int place)
{
	int	quote;
	int	i;

	i = 0;
	quote = 0;
	while (i <= place)
	{
		if (line[i] == '\"')
			quote++;
		i++;
	}
	if (quote % 2 == 0)
		return (0);
	return (1);
}

void	add_var(int *i, int *j, char *var, char *new)
{
	while (*var)
	{
		new[*j] = *var;
		var++;
		(*j)++;
	}
	(*i)++;
}

void	add_var_quoted(int *i, int *j, char *var, char *new)
{
	new[*j] = '"';
	(*j)++;
	while (*var)
	{
		new[*j] = *var;
		var++;
		(*j)++;
	}
	new[*j] = '"';
	(*j)++;
	(*i)++;
}

void	skip_var_name(char *line, int *i)
{
	while (line[*i] && !ft_isblank(line[*i]) && !is_special_char(line[*i])
		&& line[*i] != '"' && line[*i] != '\\' && line[*i] != '$'
		&& line[*i] != '=' && line[*i] != '/' && line[*i - 1] != '?')
		(*i)++;
}

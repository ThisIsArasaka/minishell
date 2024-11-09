/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:49:33 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/08 11:42:38 by olardeux         ###   ########.fr       */
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

int	in_quote_copy(t_token *new, char *line, int *pos)
{
	int		quote_count;
	char	quote;

	quote_count = 0;
	quote = line[*pos];
	quote_count = quote_count_init(line, pos);
	if (quote_count == 0)
		return (new->token = ft_add_char(new->token, '\0'), 1);
	while (line[*pos] && quote_count > 0)
	{
		if (line[*pos] == quote)
		{
			(*pos)++;
			break ;
		}
		else
		{
			new->token = ft_add_char(new->token, line[*pos]);
			if (!new->token)
				return (0);
			(*pos)++;
		}
	}
	return (1);
}

int	add_quote(t_token *new, char *line, int *pos)
{
	if (line[*pos] == '"' || line[*pos] == '\'')
	{
		if (!in_quote_copy(new, line, pos))
			return (0);
	}
	else
	{
		new->token = ft_add_char(new->token, line[*pos]);
		if (!new->token)
			return (0);
		(*pos)++;
	}
	return (1);
}

t_token	*add_quote_token(t_token *tokens, char *line, int *i)
{
	t_token	*new;
	t_token	*tmp;
	int		j;

	j = 0;
	new = add_new_token(tokens);
	if (!new)
		return (NULL);
	while (line[j] && ft_isblank(line[j]))
		j++;
	while (line[j] && !ft_isblank(line[j]) && !is_special_char(line[j]))
	{
		if (!add_quote(new, line, &j))
			return (free_tokens(new), NULL);
	}
	*i += j;
	new->type = WORD;
	new->next = NULL;
	if (!tokens)
		return (new);
	tmp = tokens;
	while (tmp)
		tmp = tmp->next;
	tmp = new;
	return (tokens);
}

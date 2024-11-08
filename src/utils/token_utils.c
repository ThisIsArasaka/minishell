/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:01:02 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/08 11:45:21 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokens_count(t_token *token)
{
	t_token	*tmp;
	int		count;

	tmp = token;
	count = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUTPUT || tmp->type == APPEND)
		{
			if (!tmp->next || tmp->next->type == OUTPUT
				|| tmp->next->type == APPEND)
				return (error_msg(SYNTAX_ERROR, NULL), -1);
			tmp = tmp->next;
		}
		else if (tmp->type == INPUT || tmp->type == HEREDOC)
		{
			if (!tmp->next || tmp->next->type == INPUT
				|| tmp->next->type == HEREDOC)
				return (error_msg(SYNTAX_ERROR, NULL), -1);
			tmp = tmp->next;
		}
		else
		{
			count++;
			tmp = tmp->next;
		}
	}
	return (count);
}

t_token	*add_new_token(t_token *tokens)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	new->token = NULL;
	if (!tokens)
		return (new);
	tmp = tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (new);
}

void	assign_token(t_token *new)
{
	if (ft_strncmp(new->token, ">", 2) == 0)
		new->type = OUTPUT;
	else if (ft_strncmp(new->token, ">>", 3) == 0)
		new->type = APPEND;
	else if (ft_strncmp(new->token, "<", 2) == 0)
		new->type = INPUT;
	else if (ft_strncmp(new->token, "<<", 3) == 0)
		new->type = HEREDOC;
	else if (ft_strncmp(new->token, "|", 2) == 0)
		new->type = PIPE;
	else
		new->type = WORD;
}

t_token	*add_token(t_parsing *parsing, char *line, int token_len)
{
	int		i;
	t_token	*new;
	t_token	*tmp;

	i = 0;
	new = add_new_token(parsing->tokens);
	while (line[i] && ft_isblank(line[i]))
	{
		i++;
		token_len--;
	}
	new->token = ft_substr(line, i, token_len);
	if (!new->token)
		return (free_tokens(new), NULL);
	new->next = NULL;
	assign_token(new);
	if (!parsing->tokens)
		return (new);
	tmp = parsing->tokens;
	while (tmp)
		tmp = tmp->next;
	tmp = new;
	return (parsing->tokens);
}

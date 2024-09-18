/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:53:32 by olardeux          #+#    #+#             */
/*   Updated: 2024/09/18 11:58:32 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokens_count(char **token, char sep_end)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i] && token[i][0] != sep_end)
	{
		printf("token[%d] = %s\n", i, token[i]);
		if (token[i][0] == '>')
			i += 2;
		else if (token[i][0] == '<')
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	**token_copy(char **tokens, int token_count)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (token_count + 2));
	if (!new)
		return (NULL);
	while (i < token_count)
	{
		new[i] = ft_strdup(tokens[i]);
		if (!new[i])
			return (free_tokens(new), NULL);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	**add_token(char **tokens, char *line, int tokens_count, int token_len)
{
	char	**new;
	int		i;

	i = 0;
	new = token_copy(tokens, tokens_count);
	if (!new)
		return (free_tokens(tokens), NULL);
	while (line[i] && ft_isblank(line[i]))
	{
		i++;
		token_len--;
	}
	new[tokens_count] = ft_substr(line, i, token_len);
	if (!new[tokens_count])
		return (free_tokens(new), NULL);
	new[tokens_count + 1] = NULL;
	if (tokens)
		free_tokens(tokens);
	return (new);
}

char	**token_split(char *line)
{
	int		i;
	int		token_start;
	int		token_count;
	char	**tokens;

	i = 0;
	tokens = NULL;
	token_start = 0;
	token_count = 0;
	while (line[i])
	{
		if (ft_isblank(line[i]) && i > 0 && !ft_isblank(line[i - 1]))
		{
			tokens = add_token(tokens, line + token_start, token_count, i
					- token_start);
			token_start = i;
			token_count++;
		}
		else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			if (i > 0 && !ft_isblank(line[i - 1]))
			{
				tokens = add_token(tokens, line + token_start, token_count, i
						- token_start);
				token_count++;
			}
			if (line[i + 1] == '>')
			{
				tokens = add_token(tokens, line + i, token_count, 2);
				i += 2;
			}
			else
			{
				tokens = add_token(tokens, line + i, token_count, 1);
				i++;
			}
			token_count++;
			token_start = i;
		}
		else if (line[i] == '"' || line[i] == '\'')
		{
			i = token_start;
			tokens = add_quote_token(tokens, line + token_start, token_count,
					&i);
			token_count++;
			token_start = i;
			printf("line[%d] = %c\n", i, line[i]);
			if (!line[i])
				break ;
		}
		i++;
	}
	if (i > 0 && !ft_isblank(line[i - 1]) && line[i - 1] != '\'' && line[i
		- 1] != '"')
	{
		tokens = add_token(tokens, line + token_start, token_count, i
				- token_start);
		token_count++;
	}
	return (tokens);
}

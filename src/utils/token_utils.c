/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:01:02 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/05 07:10:03 by olardeux         ###   ########.fr       */
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
		if (token[i][0] == '>' && (token[i][1] == '\0' || (token[i][1] == '>'
					&& token[i][2] == '\0')))
			i += 2;
		else if (token[i][0] == '<' && (token[i][1] == '\0'
				|| (token[i][1] == '<' && token[i][2] == '\0')))
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

char	**add_token(t_parsing *parsing, char *line, int tokens_count,
		int token_len)
{
	char	**new;
	int		i;

	i = 0;
	new = token_copy(parsing->tokens, tokens_count);
	if (!new)
		return (free_tokens(parsing->tokens), NULL);
	while (line[i] && ft_isblank(line[i]))
	{
		i++;
		token_len--;
	}
	new[tokens_count] = ft_substr(line, i, token_len);
	if (!new[tokens_count])
		return (free_tokens(new), NULL);
	new[tokens_count + 1] = NULL;
	if (parsing->tokens)
		free_tokens(parsing->tokens);
	return (new);
}

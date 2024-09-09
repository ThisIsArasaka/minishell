/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:20:11 by olardeux          #+#    #+#             */
/*   Updated: 2024/09/06 13:08:56 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	last_char(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (str[i - 1]);
}

int	ft_isblank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

char	*ft_add_char_pos(char *str, char c, int pos)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (i == pos)
		{
			new[j] = c;
			j++;
		}
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = 0;
	free(str);
	return (new);
}

char	*ft_add_char(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	if (str == NULL)
	{
		new = (char *)malloc(2);
		if (!new)
			return (NULL);
		new[0] = c;
		new[1] = NULL;
		return (free(str), new);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = 0;
	free(str);
	return (new);
}

int	quote_in_token(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '"' || token[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:20:11 by olardeux          #+#    #+#             */
/*   Updated: 2024/10/10 04:19:32 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isblank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
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
		new[1] = '\0';
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

int	is_special_char(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:20:11 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/24 15:39:40 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	last_char(char *str)
{
	int	i;

	i = 0;
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

int	tokens_count(char **token, char sep_end)
{
	int	i;
	int	inquote;
	int	count;

	i = 0;
	inquote = 0;
	count = 0;
	while (token[i] && (!inquote && token[i][0] != sep_end))
	{
		if (token[i][0] == '"' || last_char(token[i]) == '"')
			inquote = !inquote;
		if (!inquote && ft_strncmp(token[i], ">", 2) == 0)
			i++;
		if (!inquote && ft_strncmp(token[i], "<", 2) == 0)
			i++;
		count++;
		i++;
	}
	return (count);
}

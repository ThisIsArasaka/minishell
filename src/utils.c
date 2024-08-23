/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:20:11 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/23 10:31:59 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_len(char *line, char sep)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != sep)
		i++;
	return (i);
}

int	ft_isblank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	words_count(char *str, char sep_end)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != sep_end || str[i])
	{
		if (!ft_isblank(str[i]) && (i == 0 || ft_isblank(str[i - 1])))
			count++;
		i++;
	}
	return (i);
}

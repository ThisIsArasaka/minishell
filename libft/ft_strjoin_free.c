/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 05:01:07 by olardeux          #+#    #+#             */
/*   Updated: 2024/10/10 05:01:37 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*sjoin;
	int		l1;
	int		l2;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	sjoin = (char *)malloc(((l1 + l2) + 1) * sizeof(char));
	if (!sjoin)
		return (0);
	while (s1[i] != 0)
	{
		sjoin[i] = s1[i];
		i++;
	}
	while (s2[i - l1] != 0)
	{
		sjoin[i] = s2[i - l1];
		i++;
	}
	return ((sjoin[i] = '\0', free(s1)), sjoin);
}

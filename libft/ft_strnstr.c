/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:12:29 by olardeux          #+#    #+#             */
/*   Updated: 2023/11/24 14:49:26 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_s2;

	if (!big && !len)
		return (NULL);
	if (!little[0])
		return ((char *)big);
	i = 0;
	len_s2 = ft_strlen(little);
	while (big[i] && (i + len_s2 - 1) < len)
	{
		j = 0;
		while (little[j] && big[i + j] == little[j])
		{
			if (j == len_s2 - 1)
				return ((char *)(big + i));
			j++;
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:32:35 by olardeux          #+#    #+#             */
/*   Updated: 2023/11/15 12:32:38 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	srch;

	i = 0;
	srch = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == srch)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == srch)
		return ((char *)s + i);
	return (0);
}

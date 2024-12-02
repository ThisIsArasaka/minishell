/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:31:17 by olardeux          #+#    #+#             */
/*   Updated: 2023/11/15 12:31:20 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	srch;

	i = ft_strlen(s);
	srch = (char)c;
	while (i >= 0)
	{
		if (s[i] == srch)
			return ((char *)s + i);
		i--;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:16:02 by olardeux          #+#    #+#             */
/*   Updated: 2023/11/24 14:48:04 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_size;

	if (!dst && !size)
		return (0);
	i = 0;
	dst_size = (size_t)ft_strlen(dst);
	if (dst_size < size - 1 && size > 0)
	{
		while (src[i] && (i + dst_size) < size - 1)
		{
			dst[dst_size + i] = src[i];
			i++;
		}
		dst[dst_size + i] = '\0';
	}
	if (size > dst_size)
		return (dst_size + ft_strlen(src));
	return (size + ft_strlen(src));
}

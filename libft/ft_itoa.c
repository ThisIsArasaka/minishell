/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:29:53 by olardeux          #+#    #+#             */
/*   Updated: 2023/11/17 15:09:30 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n = n * -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*nb_itoa(char *itoa, int c, long int n, int i)
{
	while (c > i)
	{
		c--;
		itoa[c] = (n % 10) + '0';
		n /= 10;
	}
	return (itoa);
}

char	*ft_itoa(int num)
{
	char		*itoa;
	int			i;
	long int	n;
	int			c;

	i = 0;
	n = num;
	c = count_size(n);
	if (n < 0 || c == 0)
		c++;
	itoa = (char *)malloc((c + 1) * sizeof(char));
	if (!itoa)
		return (0);
	if (n < 0)
	{
		n = n * -1;
		itoa[0] = '-';
		i++;
	}
	itoa[c] = '\0';
	return (nb_itoa(itoa, c, n, i));
}

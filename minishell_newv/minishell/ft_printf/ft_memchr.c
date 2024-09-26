/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:50:43 by anasser-          #+#    #+#             */
/*   Updated: 2024/06/11 21:50:50 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*arr;

	arr = (unsigned char *) str;
	i = 0;
	if (c > 256)
		c = c % 256;
	while (i < n)
	{
		if (arr[i] == c)
			return (arr + i);
		i++;
	}
	return (NULL);
}

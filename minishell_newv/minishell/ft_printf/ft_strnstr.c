/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:52:28 by anasser-          #+#    #+#             */
/*   Updated: 2024/06/11 21:52:38 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_little;
	size_t	len_big;
	size_t	i;

	len_big = (size_t)ft_strlen(big);
	len_little = (size_t)ft_strlen(little);
	if (len_little == 0)
		return ((char *) big);
	if (len_big == 0)
		return (0);
	i = 0;
	while (i < len && (len - i >= len_little))
	{
		if (big[i] == little[0])
		{
			if (!ft_strncmp(big + i, little, len_little))
				return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}

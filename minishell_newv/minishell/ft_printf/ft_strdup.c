/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:02:23 by anasser-          #+#    #+#             */
/*   Updated: 2024/06/11 22:02:33 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup(const char *str)
{
	char	*dest;
	int		len;
	int		j;

	j = 0;
	len = ft_strlen(str);
	dest = (char *) malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	while (j < len)
	{
		dest[j] = str[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

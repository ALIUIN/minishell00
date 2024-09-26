/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:56:40 by anasser-          #+#    #+#             */
/*   Updated: 2024/06/18 16:40:26 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*res;
	char	*p;
	char	tmp;

	tmp = (char)c;
	res = (char *)s;
	len = 0;
	p = NULL;
	if (c == '\0')
		return (res + ft_strlen(s));
	while (res[len])
	{
		if (res[len] == tmp)
			p = &res[len];
		len++;
	}
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:28:01 by anasser-          #+#    #+#             */
/*   Updated: 2024/06/18 19:28:03 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *__format, ...)
{
	va_list		ap;
	char		*s;
	int			count;
	int			res;

	count = 0;
	s = (char *)__format;
	va_start(ap, __format);
	while (*s)
	{
		if (*s == '%')
		{
			res = ft_put(++s, ap);
			if (res < 0)
				return (ft_puterror(s + 1, count));
			count += res;
		}
		else
			count += ft_putchar_fd(*s, 1);
		s++;
	}
	va_end(ap);
	return (count);
}

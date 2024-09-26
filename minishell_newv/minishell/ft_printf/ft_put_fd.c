/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:43:26 by anasser-          #+#    #+#             */
/*   Updated: 2024/06/20 10:44:26 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_putadr_fd(void *ptr, int fd)
{
	unsigned long long	addr;
	int					count;

	if (!ptr)
		return (ft_putstr_fd("(nil)", fd));
	addr = (unsigned long long)ptr;
	count = ft_putstr_fd("0x", fd);
	return (count + ft_hex(addr, fd, 0));
}

int	ft_hex(unsigned long long l, int fd, int capitalise)
{
	char	*symbols;
	int		x;

	symbols = "0123456789abcdef";
	if (capitalise)
		symbols = "0123456789ABCDEF";
	if (l < 16)
	{
		ft_putchar_fd(symbols[l], fd);
		return (1);
	}
	x = ft_hex(l / 16, fd, capitalise);
	x += ft_hex(l % 16, fd, capitalise);
	return (x);
}

int	ft_putnbrbase_fd(long long l, int fd, int base, int capitalise)
{
	char	*symbols;
	int		x;
	long	sign;

	sign = -1;
	symbols = "0123456789abcdef";
	if (capitalise)
		symbols = "0123456789ABCDEF";
	if (l < 0)
	{
		ft_putchar_fd('-', fd);
		return (1 + ft_putnbrbase_fd(sign * l, fd, base, capitalise));
	}
	else if (l < base)
	{
		ft_putchar_fd(symbols[l], fd);
		return (1);
	}
	x = ft_putnbrbase_fd(l / base, fd, base, capitalise);
	x += ft_putnbrbase_fd(l % base, fd, base, capitalise);
	return (x);
}

int	ft_put(const char *s, va_list ap)
{
	if (*s == '%')
		return (ft_putchar_fd(*s, 1));
	else if (*s == 'c')
		return (ft_putchar_fd(va_arg(ap, int), 1));
	else if (*s == 's')
		return (ft_putstrhand_fd(va_arg(ap, char *), 1));
	else if (*s == 'p')
		return (ft_putadr_fd(va_arg(ap, void *), 1));
	else if (*s == 'i')
		return (ft_putnbrbase_fd((long long)va_arg(ap, int), 1, 10, 0));
	else if (*s == 'd')
		return (ft_putnbrbase_fd(va_arg(ap, int), 1, 10, 0));
	else if (*s == 'u')
		return (ft_putnbrbase_fd(va_arg(ap, unsigned int), 1, 10, 0));
	else if (*s == 'x')
		return (ft_hex((unsigned long long)va_arg(ap, unsigned int), 1, 0));
	else if (*s == 'X')
		return (ft_hex((unsigned long long)va_arg(ap, unsigned int), 1, 1));
	else
		return (-1);
}

int	ft_puterror(char *c, int curr)
{
	int	i;

	i = ft_putchar_fd(*c, 1);
	i += ft_putendl_fd(" is not a deffined", 1);
	return (curr + i);
}

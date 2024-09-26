/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:52:46 by anasser-          #+#    #+#             */
/*   Updated: 2024/06/12 17:52:48 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		return (2 + ft_putnbr_fd(147483648, fd));
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		return (1 + ft_putnbr_fd(-n, fd));
	}
	if (n >= 10)
	{
		return (ft_putnbr_fd(n / 10, fd) + ft_putnbr_fd(n % 10, fd));
	}
	else
	{
		return (ft_putchar_fd(n + 48, fd));
	}
}

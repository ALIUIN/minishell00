/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:49:37 by anasser-          #+#    #+#             */
/*   Updated: 2024/06/11 21:49:47 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	void	*mem;

	if (element_size != 0 && num_elements > 2147483647 / element_size)
		return (0);
	mem = (void *)malloc(element_size * num_elements);
	if (!mem)
		return (0);
	ft_bzero(mem, element_size * num_elements);
	return (mem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:56:01 by anasser-          #+#    #+#             */
/*   Updated: 2024/06/12 17:56:05 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*arr;
	unsigned int	src_len;

	src_len = ft_strlen(s);
	if (!s)
		return (0);
	if (start >= src_len)
		return (ft_strdup(""));
	if (src_len - start < len)
		len = src_len - start;
	arr = malloc((len + 1) * sizeof(char));
	if (!arr)
		return (arr);
	ft_strlcpy(arr, s + start, len + 1);
	return (arr);
}

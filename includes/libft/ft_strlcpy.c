/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:55:42 by astefans          #+#    #+#             */
/*   Updated: 2024/03/01 22:40:19 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (src_len + 1 < destsize)
		ft_memcpy(dest, src, src_len + 1);
	else if (destsize != 0)
	{
		ft_memcpy(dest, src, destsize - 1);
		dest[destsize - 1] = 0;
	}
	return (src_len);
}

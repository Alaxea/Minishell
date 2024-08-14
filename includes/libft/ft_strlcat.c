/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:05:14 by astefans          #+#    #+#             */
/*   Updated: 2024/03/08 11:29:31 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;
	size_t	l;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	l = dest_len;
	if (dest_len < size - 1 && size > 0)
	{
		while (src[i] && (dest_len + i < size - 1))
		{
			dest[l] = src[i];
			l++;
			i++;
		}
		dest[l] = '\0';
	}
	if (dest_len >= size)
		dest_len = size;
	return (dest_len + src_len);
}

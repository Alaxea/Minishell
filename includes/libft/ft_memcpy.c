/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:39:29 by astefans          #+#    #+#             */
/*   Updated: 2024/03/01 22:34:03 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (dest == (void *)0 && src == (void *)0)
		return (dest);
	tmp_dst = (unsigned char *) dest;
	tmp_src = (unsigned char *) src;
	while (n--)
		*(tmp_dst++) = *(tmp_src++);
	return (dest);
}

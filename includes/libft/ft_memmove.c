/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:12:56 by astefans          #+#    #+#             */
/*   Updated: 2024/03/07 21:11:48 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*move_dst;
	unsigned char	*move_src;
	size_t			i;

	move_dst = (unsigned char *) dst;
	move_src = (unsigned char *) src;
	if (!move_dst && !move_src)
		return (NULL);
	i = 0;
	if (move_dst > move_src)
		while (n--)
			move_dst[n] = move_src[n];
	else
	{
		while (n--)
		{
			move_dst[i] = move_src[i];
			i++;
		}
	}
	return (move_dst);
}

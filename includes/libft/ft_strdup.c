/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:25:29 by astefans          #+#    #+#             */
/*   Updated: 2024/03/07 22:16:36 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	len;

	len = ft_strlen(src);
	dest = (char *)malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	else
	{
		ft_strlcpy(dest, src, len + 1);
		return (dest);
	}
}

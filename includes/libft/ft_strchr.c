/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:37:49 by astefans          #+#    #+#             */
/*   Updated: 2024/03/09 16:51:52 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	cc;
	int		i;

	str = (char *)s;
	i = 0;
	cc = c;
	while (str[i] != cc && str[i] != 0)
		str++;
	if (*str == cc)
		return (str);
	else
		return (NULL);
}

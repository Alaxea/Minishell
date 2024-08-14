/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:36:38 by astefans          #+#    #+#             */
/*   Updated: 2024/03/07 18:50:43 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int nbr)
{
	int	count;

	count = 0;
	if (nbr <= 0)
		count++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int nbr)
{
	char			*result;
	int				size;
	unsigned int	nb;

	nb = nbr;
	size = int_len(nbr) + 1;
	result = (char *)malloc(size * sizeof(char));
	if (!result)
		return (NULL);
	if (nbr < 0)
	{
		nb = -nbr;
		result[0] = '-';
	}
	if (nbr == 0)
		result[0] = '0';
	result[--size] = '\0';
	while (--size >= 0 && nb)
	{
		result[size] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (result);
}

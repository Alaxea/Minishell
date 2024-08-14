/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:16:23 by astefans          #+#    #+#             */
/*   Updated: 2024/03/01 22:30:23 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>

int main(void)
{
	char testChar = 'L';
	if (ft_isascii(testChar))
		printf("%c is an ASCII character", testChar);
	else
		printf("%c is not an ASCII character", testChar);
	return(0);
}*/

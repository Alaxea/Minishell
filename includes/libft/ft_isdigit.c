/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:18:00 by astefans          #+#    #+#             */
/*   Updated: 2024/03/01 22:30:58 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>

int main(void)
{
	char testChar = '4';
	if(ft_isdigit(testChar))
		printf("%c is an digit character\n", testChar);
	else
		printf("%c is not an digit character\n", testChar);
	return(0);
}
*/

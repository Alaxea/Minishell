/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:31:21 by astefans          #+#    #+#             */
/*   Updated: 2024/02/28 16:50:54 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

int	ft_isalpha(int c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
		return (1);
	else
		return (0);
}

/*#include <stdio.h>

int main(void)
{
	char testChar = ' ';
	if (ft_isalpha(testChar))
		printf("%c is an alphabet character\n", testChar);
	else
		printf("%c is not an alphabet character\n", testChar);
	return(0);
}
*/

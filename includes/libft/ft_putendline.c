/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendline_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:44:06 by astefans          #+#    #+#             */
/*   Updated: 2024/08/29 13:45:43 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendline(const char *s, int fd)
{
	if (s)
	{
        while (*s) 
        {
            ft_putchar_fd(*s, fd);
            s++;
        }
	}
    ft_putchar_fd('\n', fd);
}

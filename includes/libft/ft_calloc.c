/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:27:17 by astefans          #+#    #+#             */
/*   Updated: 2024/03/05 16:41:35 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	void	*tmp_ptr;

	if (num_elements >= 4294967295 || element_size >= 4294967295)
		return (NULL);
	tmp_ptr = malloc(num_elements * element_size);
	if (!tmp_ptr)
		return (NULL);
	ft_bzero(tmp_ptr, num_elements * element_size);
	return (tmp_ptr);
}

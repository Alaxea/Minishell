/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:02:17 by astefans          #+#    #+#             */
/*   Updated: 2024/11/05 17:52:06 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void free_arguments(char **arguments) 
{
    int i;

	i = 0;
    if (arguments)
    {
        while (arguments[i]) 
	    {
            free(arguments[i]);
            i++;
        }
        free(arguments);
    }
}
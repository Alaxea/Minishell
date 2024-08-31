/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:10:55 by astefans          #+#    #+#             */
/*   Updated: 2024/08/29 11:11:17 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	usage(void)
{
	ft_putendl_fd("Error: Bad arguments", 1);
	ft_putendl_fd("Usage: ./minishell <cmd>", 1);
	exit(EXIT_SUCCESS);
}

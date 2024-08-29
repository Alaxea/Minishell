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

int	error_msg(const char *prompt, const char *arg, const char *msg, int exit_code)
{
	if (prompt != NULL)
	{
		ft_putstring(prompt, 2);
		ft_putstring(">> ", 2);
	}
	if (arg != NULL)
	{
		ft_putstring(arg, 2);
		ft_putstring(">> ", 2);
	}
	ft_putstring(msg, 2);
    ft_putendl_fd("\n", 2);
	return (exit_code);
}
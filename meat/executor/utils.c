/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:30:42 by astefans          #+#    #+#             */
/*   Updated: 2024/11/12 16:45:32 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_open_error(int fd, char *error_msg)
{
	if (fd < 0)
	{
		ft_putstr_fd(error_msg, 2);
		exit(1);
	}
}

int	error_command_not_found(void)
{
	ft_putstr_fd("Command not found\n", STDERR_FILENO);
	return (-1);
}

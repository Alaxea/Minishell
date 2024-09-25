/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:25:19 by astefans          #+#    #+#             */
/*   Updated: 2024/09/25 12:25:26 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_pipe(t_simple_cmd *current)
{
	if (current->prev == NULL && current->next != NULL)
		dup2(current->fd_out, STDOUT_FILENO);
	if (current->prev != NULL && current->next != NULL)
	{
		dup2(current->prev->fd_in, STDIN_FILENO);
		dup2(current->fd_out, STDOUT_FILENO);
	}
	if (current->next == NULL && current->prev != NULL)
		dup2(current->prev->fd_in, STDIN_FILENO);
}

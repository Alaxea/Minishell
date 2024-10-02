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

int	exec_commands(env, commands)
{
	int	i;
	int	result;

	//stworz pipes
	i = 0;
	while (commands istnieją)
	{
		result = //exec komendy();
		pid komendy = 0;
		if (result == -1)
			//forkuj dzieci();
		else
			waitpid(last_result) = result;
		i++;
	}
	//zamknij fds();
	return (czekaj na dzieci i zwróc result());
}
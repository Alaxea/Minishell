/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:01:19 by astefans          #+#    #+#             */
/*   Updated: 2024/11/20 23:50:39 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipes(t_simple_cmd *cmd)
{
	t_simple_cmd	*current;
	int				fd_in;
	int				fd_out;

	current = cmd;
	while (current)
	{
		fd_in = current->fd_in;
		fd_out = current->fd_out;
		if (fd_in > 2)
		{
			close(fd_in);
			current->fd_in = -1;
		}
		if (fd_out > 2)
		{
			close(fd_out);
			current->fd_out = -1;
		}
		current = current->next;
	}
}

int	create_pipes(t_data *env, t_simple_cmd *cmd)
{
	t_simple_cmd	*current;

	current = cmd;
	while (current->next)
	{
		if (pipe(env->fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
		current->fd_out = env->fd[1];
		current->next->fd_in = env->fd[0];
		current = current->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:09:57 by astefans          #+#    #+#             */
/*   Updated: 2024/08/29 11:10:16 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_data(t_data *data, bool clear_history)
{
	if (data && data->user_input)
	{
		free(data->user_input);
		data->user_input = NULL;
	}
	if (data && data->token)
		free(data->token);
	if (data && data->cmd)
		free(data->cmd);
	if (clear_history == true)
	{
		if (data && data->current_dir)
			free(data->current_dir);
	    if (data && data->old_dir)
			free(data->old_dir);
		rl_clear_history();
	}
}

/*frees a pointer and sets NULL*/
void	free_pointer(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	close_fds(t_simple_cmd *command)
{
	if (command->io_fds)
	{
		if (command->io_fds->fd_in != -1)
			close(command->io_fds->fd_in);
		if (command->io_fds->fd_out != -1)
			close(command->io_fds->fd_out);
	}
}

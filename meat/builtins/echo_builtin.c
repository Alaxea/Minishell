/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:21:26 by astefans          #+#    #+#             */
/*   Updated: 2024/10/03 15:48:09 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redir_builtin(t_simple_cmd *cmd)
{
	if (cmd->output_path)
		cmd->fd_out = open(cmd->output_path, O_WRONLY | O_CREAT | O_TRUNC);
	else if (cmd->output_path_append)
		cmd->fd_out = open(cmd->output_path_append, O_WRONLY | O_APPEND | O_CREAT);
	else
		cmd->fd_out = 1;
}

static int	echo_helper(t_simple_cmd *com, int *new_line);

int	echo_builtin(t_simple_cmd *com)
{
	int	new_line;
	int	ret_val;
	int	i;

	i = 1;
	new_line = 1;
	ret_val = echo_helper(com, &new_line);
	if (com->cmd && com->cmd[i] != NULL)
	{
		ft_putstr_fd(com->cmd[i], com->fd_out);
		i++;
		while (com->cmd[i] != NULL)
		{
			ft_putstr_fd(" ", com->fd_out);
			ft_putstr_fd(com->cmd[i], com->fd_out);
			i++;
		}
	}
	if (new_line)
		ft_putstr_fd("\n", com->fd_out);
	return (ret_val);
}

static int	echo_helper(t_simple_cmd *com, int *new_line)
{
	int	i;

	i = 0;
	redir_builtin(com);
	if (com->flags)
	{
		while (com->flags[i])
		{
			if (com->flags[i++] != 'n')
			{
				ft_putstr_fd("Invalid flag\n", 2);
				return (-1);
			}
		}
		if (com->flags[0] == 'n')
			*new_line = 0;
	}
	return (0);
}
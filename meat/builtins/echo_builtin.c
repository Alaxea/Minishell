/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:21:26 by astefans          #+#    #+#             */
/*   Updated: 2024/10/30 14:33:28 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redir_builtin(t_simple_cmd *cmd)
{
	if (cmd->output_path)
		cmd->fd_out = open(cmd->output_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (cmd->output_path_append)
		cmd->fd_out = open(cmd->output_path_append, O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		cmd->fd_out = 1;
}

static int	echo_helper(t_simple_cmd *sc, int *new_line);

int	echo_builtin(t_simple_cmd *cmd)
{
	int	new_line;
	int	ret_val;

	new_line = 1;
	ret_val = echo_helper(cmd, &new_line);
	if (cmd->cmd && cmd->cmd[new_line])
	{
		ft_putstr_fd(cmd->cmd[new_line], cmd->fd_out);
		new_line++;
		while (cmd->cmd[new_line] != NULL)
		{
			ft_putstr_fd(" ", cmd->fd_out);
			ft_putstr_fd(cmd->cmd[new_line], cmd->fd_out);
			new_line++;
		}
	}
	if (ret_val)
		ft_putstr_fd("\n", cmd->fd_out);
	return (1);
}

static int	echo_helper(t_simple_cmd *sc, int *new_start)
{
	int	ret_value;
	int	i;
	
	i = 1;
	ret_value = 1;
	redir_builtin(sc);
	while (sc->cmd[i][0] == '-' && sc->cmd[i][1] == 'n')
	{
		ret_value = 0;
		(*new_start)++;
		i++;
	}
	return (ret_value);
}
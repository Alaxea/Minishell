/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:21:26 by astefans          #+#    #+#             */
/*   Updated: 2024/10/17 22:42:29 by alicja           ###   ########.fr       */
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

static int	echo_helper(t_simple_cmd *cmd, int *new_line);

int	echo_builtin(t_simple_cmd *cmd)
{
	int	new_line;
	int	ret_val;
	int	i;

	i = 1;
	new_line = 1;
	ret_val = echo_helper(cmd, &new_line);
	if (ret_val != 0)
		return (ret_val);
	if (cmd->cmd && cmd->cmd[i] != NULL)
	{
		ft_putstr_fd(cmd->cmd[i], cmd->fd_out);
		i++;
		while (cmd->cmd[i] != NULL)
		{
			ft_putstr_fd(" ", cmd->fd_out);
			ft_putstr_fd(cmd->cmd[i], cmd->fd_out);
			i++;
		}
	}
	if (new_line)
		ft_putstr_fd("\n", cmd->fd_out);
	return (ret_val);
}

static int	echo_helper(t_simple_cmd *cmd, int *new_line)
{
	int	i;

	i = 0;
	redir_builtin(cmd);
	if (cmd->flags == NULL)
        return (0);
	while (cmd->flags[i])
	{
		if (cmd->flags[i++] != 'n')
		{
			ft_putstr_fd("Invalid flag\n", 2);
			return (-1);
		}
	}
	if (cmd->flags[0] == 'n')
		*new_line = 0;
	return (0);
}
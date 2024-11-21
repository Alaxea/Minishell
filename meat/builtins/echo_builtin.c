/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:21:26 by astefans          #+#    #+#             */
/*   Updated: 2024/11/21 18:33:59 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	echo_builtin(t_simple_cmd *cmd)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	while (cmd->cmd[i])
	{
		while (ft_strcmp(cmd->cmd[i], "-n") == 0)
		{
			flag = 1;
			i++;
		}
		write(STDOUT_FILENO, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		if (cmd->cmd[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:42:19 by astefans          #+#    #+#             */
/*   Updated: 2024/11/13 11:33:34 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*function checks if parameter passed is a number accept
 * one '-' or '+' on the beggining.*/
static int	ft_overflow_int(char *str)
{
	int	value;
	int	i;
	int	digit;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (ft_isdigit(str[i]) && str[i + 1] == '\0')
		return (0);
	value = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			digit = str[i] - '0';
			if (value > (INT_MAX - digit) / 10)
				return (1);
			value = value * 10 + digit;
			i++;
		}
		else
			return (1);
	}
	return (0);
}

int	exit_builtin(t_data *env, t_simple_cmd *cmd)
{
	write(1, "exit\n", 5);
	if (!cmd->cmd[1])
		exit_shell(env, NULL, 0);
	if (cmd->cmd[2])
	{
		ft_putstr_fd("Too many arguments\n", 2);
		return (1);
	}
	if (!ft_isdigit(cmd->cmd[1][0]) || ft_overflow_int(cmd->cmd[1]))
	{
		ft_putstr_fd("Numeric argument is required\n", 2);
		return (1);
	}
	exit_shell(env, NULL, ft_atoi(cmd->cmd[1]));
	return (0);
}

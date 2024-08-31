/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:42:19 by astefans          #+#    #+#             */
/*   Updated: 2024/08/26 16:42:21 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	checkout(int sign, unsigned long long num, bool *err)
{
	if ((sign == 1 && num > LONG_MAX) || (sign == -1 && num > -(unsigned long)LONG_MIN))
		*err = true;
	return(*err);
}

long long int	ft_atoi_long(const char *str, bool *err)
{
	char			*nbr;
	long long		i;
	long long		sign;
	long long		res;

	res = 0;
	sign = 1;
	i = 0;
	nbr = (char *)str;
	while (nbr[i] == 32 || (nbr[i] >= 9 && nbr[i] <= 13))
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9' )
	{
		res = res * 10 + nbr[i] - '0';
		if (checkout(sign, res, err))
			break;
		i++;
	}
	return (sign * res);
}

static int		set_exit_code(char *arg, bool *error)
{
	unsigned long long 		i;

	if(!arg)
		return (-1);
	i = 0;
	while(ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoi_long(arg, error);
	return (i % 255); /*exit code in linux is only between 0-255*/
}

static int	is_quiet_mode(t_data *data)
{
	t_simple_cmd *cmd;

	cmd = data->cmd;
	if (!cmd)
		return (0);
	if (cmd->next != NULL || cmd->prev != NULL)
		return (1);
	return (0);
}

int		exit_builtin(t_data *data, char **args)
{
	int		exit_code;
	bool		error;
	bool		mode;

	mode = is_quiet_mode(data);
	error = false;
	if (!mode && data->interactive)
		ft_putendline("exit", 2);
	if (!args || !args[1])
		exit_code = data->last_exit_code;
	else
	{
		exit_code = set_exit_code(args[1], &error);
		if (error)
			exit_code = error_msg("exit", args[1], "numeric argument required", 2);
		else if (args[2])
			return (error_msg("exit", NULL, "too many arguments", 1));
	}
	exit_shell(data, exit_code);
	return (2);
}
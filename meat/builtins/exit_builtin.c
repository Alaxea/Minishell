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

/*function checks if parameter passed is a number accept 
 * one '-' or '+' on the beggining.*/
int	ft_overflow_int(char *str)
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

int		exit_builtin(t_data *env, t_simple_cmd com)
{
	int	result;

	write(1, "exit\n", 5);
	if (com.arguments[0] == NULL)
	{
		clear_env(env);
		exit(0);
	}
	if (com.arguments[0] && com.arguments[1])
	{
		ft_putstr_fd("Too many arguments\n", 2);
		return (1);
	}
	if (!ft_isdigit(com.arguments[0] || ft_overflow_int(com.arguments[0])))
	{
		ft_putstr_fd("Numeric argument is required\n", 2);
		clear_env(env);
		return (255);
	}
	else
	{
		clear_env(env);
		result = ft_atoi(com.arguments[0]);
		if (result < 0)
			exit(255 + result);
		exit(result);
	}
}

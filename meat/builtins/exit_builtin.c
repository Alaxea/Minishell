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

int	checkout(unsigned long long nbr, int sign)
{
	int	i;

	i = 0;
	while (i < sign)
	{
		if ((nbr > LONG_MAX) || (nbr < LONG_MIN))
		{
			perror("Error");
			return (-1);
		}
		i++;
	}
	return (0);
}

long long int	ft_atoi_long(const char *str)
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
		i++;
	}
	return (sign * res);
}

static int		exit_code(char *arg, bool *error)
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
	i = ft_atoi_long(arg);
	return (i % 255); /*exit code in linux is only between 0-255*/
}

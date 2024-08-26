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

int	number_limit(long *num, int neg)
{
	int	i;

	i = 0;
	while (i < neg)
	{
		if ((num[i] > LONG_MAX) || (num[i] < LONG_MIN))
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:10:23 by astefans          #+#    #+#             */
/*   Updated: 2024/08/26 14:10:25 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	usage(void)
{
	ft_putendl_fd("Error: Bad arguments", 1);
	ft_putendl_fd("Usage: ./minishell <cmd>", 1);
	exit(EXIT_SUCCESS);
}

int	is_valid_env_var_key(char *var)
{
	int		i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (-1);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return(-1);
		i++;
	}
	return (0);
}
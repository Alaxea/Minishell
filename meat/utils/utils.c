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

/*Exits the minishell program by closing all opened
*	fds and freeing all allocated memory*/
void	exit_shell(t_data *data, int clean)
{
	if (data)
	{
		if (data->cmd && data->cmd->io_fds)
			close_fds(data->cmd);
		free_data(data, true);
	}
	exit(clean);
}
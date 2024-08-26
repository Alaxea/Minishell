/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:34:01 by astefans          #+#    #+#             */
/*   Updated: 2024/08/23 15:34:32 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		pwd_builtin(t_data *data, char **args)
{
	char	*current_working_dir;
	char	buf[PATH_MAX];

	(void)args;
	if (data->current_dir)
	{
		ft_putendl_fd(data->current_dir, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	current_working_dir = getcwd(buf, PATH_MAX);
	if (current_working_dir)
	{
		ft_putendl_fd(current_working_dir, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	perror("Error");
	return(EXIT_FAILURE);
}
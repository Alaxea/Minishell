/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:34:01 by astefans          #+#    #+#             */
/*   Updated: 2024/09/05 15:49:35 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*int		pwd_builtin(t_data *data, char **args)
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
}*/

int	pwd_builtin(t_data *data)
{
	char	*tmp;

	tmp = get_env_var(data, "PWD");
	if (!tmp || tmp[0] == '\0')
	{
		ft_putstr_fd("PWD variable is unset", 2);
		if (tmp[0] == '\0')
			free(tmp);
		return (2);
	}
	ft_putstr_fd(tmp, 1);
	ft_putstr_fd("\n", 1);
	free(tmp);
	return (0);
}
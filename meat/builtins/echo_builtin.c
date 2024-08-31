/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:21:26 by astefans          #+#    #+#             */
/*   Updated: 2024/08/22 15:21:29 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*int	echo_builtin(t_data fullcmd, t_data *info)
{
	int	i;
	int	flag;

	flag = 0;
	info->exit_code = 0;
	if (fullcmd.fullcmd->argums[1] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (info->exit_code);
	}
	if (fullcmd.fullcmd->argums[1])
	{
		if (!ft_strncmp(fullcmd.fullcmd->argums[1], "-n", ft_strlen(fullcmd.fullcmd->argums[1]))
			&& ft_strlen(fullcmd.fullcmd->argums[1]) == 2)
			flag = 1;
		i = 1 + flag;
		while (fullcmd.fullcmd->argums[i])
		{
			write(STDOUT_FILENO, fullcmd.fullcmd->argums[i],
			ft_strlen(fullcmd.fullcmd->argums[i]));
			i++;
			if (fullcmd.fullcmd->argums[i])
				write(STDOUT_FILENO, " ", 1);
		}
	}
	if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (info->exit_code);
}

int	ft_choose_builtin(t_data fullcmd, t_data *info)
{
	if (!ft_strncmp(fullcmd.fullcmd->argums[1], "echo", ft_strlen(fullcmd.fullcmd->argums[0])))
		info->exit_code = echo_builtin(fullcmd, info);
	return (info->exit_code);
}*/

int	echo(char **args, int argc, int fd)
{
	int	i;

	i = 0;
	if (argc > 0 && ft_strncmp(args[0], "-n", 2) == 0 && ft_strlen(args[0]) == 2)
    {
        i = 1; // Przesuń indeks, aby pominąć "-n"
    }
	if (argc == 0)
	{
		write(1, "\n", fd);
		return (0);
	}
	while (args[i] && !ft_strncmp(args[i], "-n", 2))
		i++;
	while (i < argc - 1)
	{
		write(fd, args[i], ft_strlen(args[i]));
        write(fd, " ", 1);
        i++;
	}
	if (i != argc)
		write(fd, args[i], ft_strlen(args[i]));
	if (ft_strncmp(args[0], "-n", 2))
		write(1, "\n", fd);
	return (0);
}
int	is_builtin(t_data *command, int fd)
{
	if (!ft_strncmp(command->command, "echo", 2))
		return (echo(command->args + 1, command->argc - 1, fd));
	return (127);
}
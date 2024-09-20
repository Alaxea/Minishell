/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:21:26 by astefans          #+#    #+#             */
/*   Updated: 2024/09/19 18:23:11 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*int	echo(char **args, int argc, int fd)
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
}*/

static int	echo_helper(t_simple_cmd *com, int *new_line);

int	echo_builtin(t_simple_cmd *com)
{
	int	new_line;
	int	ret_val;
	int	i;

	i = 1;
	new_line = 1;
	ret_val = echo_helper(com, &new_line);
	if (com->cmd && com->cmd[0] != NULL)
	{
		ft_putstr_fd(com->cmd[i], 1);
		i++;
		while (com->cmd[i] != NULL)
		{
			ft_putstr_fd(" ", 1);
			ft_putstr_fd(com->cmd[i], 1);
			i++;
		}
	}
	if (new_line)
		ft_putstr_fd("\n", 1);
	return (ret_val);
}

static int	echo_helper(t_simple_cmd *com, int *new_line)
{
	int	i;

	i = 0;
	if (com->flags)
	{
		while (com->flags[i])
		{
			if (com->flags[i++] != 'n')
			{
				ft_putstr_fd("Invalid flag\n", 2);
				return (-1);
			}
		}
		if (com->flags[0] == 'n')
			*new_line = 0;
	}
	return (0);
}
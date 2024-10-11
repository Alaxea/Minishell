/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:09:46 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/07/26 14:41:38 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	return_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}

static char	*find_the_proper_path(char *command, char **paths)
{
	char	*added_slash;
	char	*proper_path;
	int		i;

	i = 0;
	added_slash = NULL;
	proper_path = NULL;
	if (access(command, X_OK | F_OK) == 0)
		return (command);
	while (paths[i])
	{
		added_slash = ft_strjoin(paths[i], "/");
		if (!added_slash)
			return_error("malloc error\n");
		proper_path = ft_strjoin(added_slash, command);
		free(added_slash);
		if (access(proper_path, X_OK | F_OK) == -1)
			free(proper_path);
		else
			return (proper_path);
		i++;
	}
	return (proper_path);
}

char	**find_paths(char **envp)
{
	char	**paths;

	while (*envp)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
			break ;
		envp++;
	}
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		return_error("ft_split error\n");
	return (paths);
}

int	exec_prep(t_pipex_data *data, char *command, char **envp)
{
	char	*proper_path;
	char	**commands;

	commands = ft_split(command, ' ');
	proper_path = find_the_proper_path(commands[0], data->paths);
	if (execve(proper_path, commands, envp) == -1)
		return_error("execve error");
	return (EXIT_SUCCESS);
}

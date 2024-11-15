/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:16:30 by astefans          #+#    #+#             */
/*   Updated: 2024/11/15 23:35:44 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_envp_var(const char *var_name, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var_name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*check_direct_command(const char *command)
{
	if (ft_strchr(command, '/') && access(command, X_OK) == 0)
		return (ft_strdup(command));
	return (NULL);
}

static char	*check_local_command(const char *command)
{
	char	*full_path;

	if (access(command, X_OK) == 0)
	{
		full_path = ft_strjoin("./", command);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

static char	*search_in_paths(char **paths, const char *command)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = concat_path(paths[i], command);
		if (access(full_path, X_OK) == 0)
		{
			free_paths(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_full_path(const char *command, char **envp)
{
	char	*path_env;
	char	**paths;

	if (check_direct_command(command))
		return (check_direct_command(command));
	if (check_local_command(command))
		return (check_local_command(command));
	path_env = get_envp_var("PATH", envp);
	if (!path_env)
	{
		write(STDERR_FILENO, "PATH variable not found\n", 24);
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, command));
}

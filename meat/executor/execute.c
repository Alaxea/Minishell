/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:16:30 by astefans          #+#    #+#             */
/*   Updated: 2024/11/15 16:20:30 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_paths(char **paths)
{
	int		i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*concat_path(const char *dir, const char *command)
{
	char		*path;
	size_t		len_dir;
	size_t		len_cmd;

	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(command);
	path = (char *)malloc(len_dir + len_cmd + 2);
	if (!path)
		return (NULL);
	ft_strlcpy(path, dir, len_dir + 1);
	path[len_dir] = '/';
	ft_strlcpy(path + len_dir + 1, command, len_cmd + 1);
	return (path);
}

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

/*char	*get_full_path(const char *command, char **envp)
{
	char		*path_env;
	char		**paths;
	char		*full_path;
	int			i;

	if (ft_strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	if (access(command, X_OK) == 0)
	{
		full_path = ft_strjoin("./", command);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	path_env = get_env_var("PATH", envp);
	if (!path_env)
	{
		write(STDERR_FILENO, "PATH variable not found\n", 24);
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
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
	free_paths(paths);
	return (NULL);
}*/

static int	execute_child(t_simple_cmd *cmd, char *full_path, char **envp)
{
	redir_check(cmd);
	if (execve(full_path, cmd->cmd, envp) == -1)
	{
		perror("execve");
		free(full_path);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	execute_command(t_simple_cmd *cmd, char **envp)
{
	pid_t	pid;
	char	*full_path;
	int		status;

	full_path = get_full_path(cmd->cmd[0], envp);
	if (!full_path)
		return (ft_putstr_fd("Command not found\n", 2), 127);
	pid = fork();
	if (pid == 0)
		execute_child(cmd, full_path, envp);
	else if (pid > 0)
	{
		free(full_path);
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	free(full_path);
	return (ft_putstr_fd("Fork failed\n", 2), -1);
}

/*int	execute_command(t_simple_cmd *cmd, char **envp)
{
	pid_t		pid;
	char		*full_path;
	int			status;

	status = 0;
	full_path = get_full_path(cmd->cmd[0], envp);
	if (full_path == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		redir_check(cmd);
		if (execve(full_path, cmd->cmd, envp) == -1)
		{
			perror("execve");
			free(full_path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		free(full_path);
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	else
	{
		free(full_path);
		ft_putstr_fd("Fork failed\n", 2);
		return (-1);
	}
	return (status);
}*/

int	check_permission(struct stat file)
{
	if (file.st_mode & S_IXUSR)
		return (1);
	else
	{
		ft_putstr_fd("File is not executable\n", 2);
		ft_putstr_fd("This is not a file\n", 2);
	}
	return (0);
}

char	*find_script(char *script, t_data *env)
{
	char	*cwd;
	char	*result;

	if (script[0] == '.' && script[1] == '/')
	{
		cwd = set_env_var(env, "PWD");
		if (!cwd)
		{
			ft_putstr_fd("PWD not found\n", 2);
			return (NULL);
		}
		result = ft_strjoin(cwd, script + 1);
		free(cwd);
		return (result);
	}
	else
		return (ft_strdup(script));
}

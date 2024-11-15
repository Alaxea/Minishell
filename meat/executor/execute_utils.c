/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:16:30 by astefans          #+#    #+#             */
/*   Updated: 2024/11/15 23:35:55 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

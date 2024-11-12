/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:16:30 by astefans          #+#    #+#             */
/*   Updated: 2024/11/12 10:51:33 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_paths(char **paths)
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

char	*get_env_var(const char *var_name, char **envp)
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

char	*get_full_path(const char *command, char **envp)
{
	char		*path_env;
	char		**paths;
	char		*full_path;
	int			i;

	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
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
}

int	execute_command(t_simple_cmd *cmd, char **envp)
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


/*char	*find_script(char *script, t_data *env)
{
	char	*cwd;
	char	*result;

	if (script[0] == '.' && script[1] == '/')
	{
		// Pobierz bieżący katalog roboczy z env
		cwd = set_env_var(env, "PWD");
		if (!cwd)
		{
            ft_putstr_fd("PWD not found\n", 2);
            return (NULL);
        }
		// Dodaj `/` i nazwę skryptu pomijając `./`
		result = ft_strjoin(cwd, script + 1);
		free(cwd);
		return (result);
	}
	else
		return (ft_strdup(script)); // Zwróć kopię nazwy skryptu
}*/


char	*find_script(char *script, t_data *env)
{
	char	*tmp;
	char	*cwd;
	char	*result;

	// Jeśli skrypt zaczyna się od "./", dodaj bieżący katalog
	if (script[0] == '.' && script[1] == '/')
	{
		// Pobierz bieżący katalog roboczy z env
		cwd = set_env_var(env, "PWD");
		if (!cwd)
			return (NULL); // Jeśli PWD nie istnieje, zwróć NULL
		// Połącz bieżący katalog z pełną ścieżką do skryptu
		tmp = ft_strjoin(cwd, "/");
		result = ft_strjoin(tmp, script + 2); // Pomijamy "./" z początku skryptu
		free(tmp);
		free(cwd);
		 ft_putstr_fd("Script path: ", 2);
        ft_putstr_fd(result, 2);
        ft_putstr_fd("\n", 2);
		return (result);
	}
	else
		return (ft_strdup(script)); // Zwracamy kopię nazwy skryptu
}

/*char	*find_script(char *script, t_data *env)
{
	char	*tmp;
	char	*tmp2;
	char	*result;

	if (script[0] == '.')
	{
		tmp = ft_substr(script, 1, ft_strlen(script) - 1);
		tmp2 = set_env_var(env, "PWD");
		result = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
		return (result);
	}
	else
		return (script);
}*/

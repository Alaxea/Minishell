/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:16:30 by astefans          #+#    #+#             */
/*   Updated: 2024/10/07 23:36:13 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void free_paths(char **paths)
{
    int i;

    i = 0;
    while (paths[i])
    {
        free(paths[i]);
        i++;
    }
    free(paths);
}

char *concat_path(const char *dir, const char *command) //łączy katalog z nazwą komendy
{
    char *path;
    size_t len_dir;
    size_t len_cmd;

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

char *get_env_var(const char *var_name, char **envp)
{
    int i = 0;
    size_t len = ft_strlen(var_name);

    while (envp[i])
    {
        if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
            return (envp[i] + len + 1);
        i++;
    }
    return (NULL);
}

char *get_full_path(const char *command, char **envp)
{
    char *path_env;
    char **paths;
    char *full_path;
    int i;

    path_env = get_env_var("PATH", envp);
    if (!path_env)
        return (NULL);
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        full_path = concat_path(paths[i], command);
        if (!full_path)
        {
            free_paths(paths);
            return (NULL);
        }
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

int execute_command(t_simple_cmd *cmd, char **envp)
{
    pid_t pid;
    char    *full_path;
    int status;

	pid = fork();
    status = 0;
    if (pid == 0)
    {
        redir_check(cmd);
        full_path = get_full_path(cmd->cmd[0], envp);
        if (full_path == NULL)
        {
            ft_putstr_fd("Command not found\n", 2);
            exit(EXIT_FAILURE);
        }
        if (execve(full_path, cmd->cmd, envp) == -1)
        {
           ft_putstr_fd("Execution failed\n", 2);
           exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0)
    {
        
        waitpid(pid, &status, 0);
    }
    else
    {
        ft_putstr_fd("Fork failed\n", 2);
        return (-1);
    }
    return (status);
}

int     check_permission(struct stat file)
{
    if ((file.st_mode > 0) && (S_IEXEC & file.st_mode) && S_ISREG(file.st_mode))
    {
        if (file.st_mode & S_IXUSR)
            return (1);
        else
            ft_putstr_fd("File is not executable\n", 2);
    }
    else
        ft_putstr_fd("This is not a file\n", 2);
    return (0);
}

char	*find_script(char *script, t_data *env)
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
}
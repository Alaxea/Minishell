#include "../../minishell.h"

void close_pipes(t_simple_cmd *cmd)
{
    t_simple_cmd *current = cmd;
    while (current)
    {
        if (current->fd_in > 2)
        {
            close(current->fd_in);
            current->fd_in = -1;
        }
        if (current->fd_out > 2)
        {
            close(current->fd_out);
            current->fd_out = -1;
        }
        current = current->next;
    }
}

int create_pipes(t_data *env, t_simple_cmd *cmd)
{
    t_simple_cmd *current = cmd;

    while (current->next)
    {
        if (pipe(env->fd) == -1)
        {
            perror("pipe");
            return (-1);
        }
        current->fd_out = env->fd[1];
        current->next->fd_in = env->fd[0];
        current = current->next;
    }
    return (0);
}
int execute(t_simple_cmd *cmd, t_data *env) {
    t_simple_cmd *current = cmd;
    int status = 0;

    if (!current)
        return (-1);
    // Handle single command without pipes
    if (!cmd->next) {
        current->pid = fork();
        if (current->pid == 0) {
            // Child process
            if (redir_check(current) == -1)
                exit(1);

            // Execute after redirection is set up
            if (check_for_builtins(current)) 
            {
                int ret = execute_builtin(env, current);
                exit(ret);
            } 
            else 
            {
                char *full_path = get_full_path(current->cmd[0], env->envp);
                if (!full_path) 
                {
                    ft_putstr_fd("Command not found\n", 2);
                    exit(127);
                }
                execve(full_path, current->cmd, env->envp);
                perror("execve");
                free(full_path);
                exit(127);
            }
        }
        waitpid(current->pid, &status, 0);
        return WEXITSTATUS(status);
    }

    // Handle piped commands
    if (create_pipes(env, cmd) == -1) 
        return (-1);
    while (current) 
    {
        current->pid = fork();
        if (current->pid == 0) 
        {
            // Child process
            t_simple_cmd *temp = cmd;
            while (temp) 
            {
                if (temp != current) 
                {
                    if (temp->fd_in > 2) close(temp->fd_in);
                    if (temp->fd_out > 2) close(temp->fd_out);
                }
                temp = temp->next;
            }

            if (current->fd_in > 2) 
            {
                dup2(current->fd_in, STDIN_FILENO);
                close(current->fd_in);
            }
            if (current->fd_out > 2) 
            {
                dup2(current->fd_out, STDOUT_FILENO);
                close(current->fd_out);
            }
            if (check_for_builtins(current)) 
                exit(execute_builtin(env, current));
            else 
            {
                char *full_path = get_full_path(current->cmd[0], env->envp);
                if (!full_path) 
                {
                    ft_putstr_fd("Command not found\n", 2);
                    exit(127);
                }
                execve(full_path, current->cmd, env->envp);
                perror("execve");
                free(full_path);
                exit(127);
            }
        }
        current = current->next;
    }

    close_pipes(cmd);

    current = cmd;
    while (current) 
    {
        waitpid(current->pid, &status, 0);
        current = current->next;
    }
    return WEXITSTATUS(status);
}

int fork_and_execute(t_simple_cmd *cmd, t_data *env)
{
    t_simple_cmd *current = cmd;
    char *full_path;

    while (current)
    {
        if (check_for_builtins(current)) 
        {
            fflush(stdout);
            fflush(stderr);

            current->pid = fork();
            if (current->pid == 0) 
            {

            // handle file redirections
                if (redir_check(current) == -1)
                    exit(1);

            // Set up pipes first if they exist
                if (current->fd_in > 2)
                     dup2(current->fd_in, STDIN_FILENO);
                if (current->fd_out > 2)
                    dup2(current->fd_out, STDOUT_FILENO);

            // Execute the builtin
                int ret = execute_builtin(env, current);
                exit(ret);
            }
            if (current->pid < 0) 
            {
                perror("fork");
                return (-1);
            }

        // Parent process
            if (current->fd_in > 2)
                close(current->fd_in);
            if (current->fd_out > 2)
                close(current->fd_out);

            int status;
            waitpid(current->pid, &status, 0);
            return WEXITSTATUS(status);
        }
        else 
        {
            if (!(full_path = get_full_path(current->cmd[0], env->envp))) 
            {
                ft_putstr_fd("Command not found\n", 2);
                return (-1);
            }
            current->pid = fork();
            if (current->pid == 0) 
            {
                if (redir_check(current) == -1) {  // Add error check
                    exit(1);
                }
                close_pipes(cmd);
                execve(full_path, current->cmd, env->envp);
                perror("execve");
                free(full_path);
                exit(127);
            }
            if (current->pid < 0) 
            {  // Add fork error check
                perror("fork");
                free(full_path);
                return -1;
            }
            free(full_path);
        }

        if (current->fd_in > 2)
            close(current->fd_in);
        if (current->fd_out > 2)
            close(current->fd_out);

        current = current->next;
    }
    return (0);
}
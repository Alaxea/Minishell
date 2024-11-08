/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:30:42 by astefans          #+#    #+#             */
/*   Updated: 2024/11/08 23:17:06 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	in_redir(t_simple_cmd *cmd)
{
	int	fd_in;

	if (!cmd->input_path)
		return ;
	fd_in = open(cmd->input_path, O_RDONLY);
	if (fd_in < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->input_path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	cmd->saved_stdin = dup(STDIN_FILENO);
	if (cmd->saved_stdin == -1)
	{
		close(fd_in);
		exit(1);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		close(cmd->saved_stdin);
		exit(1);
	}
	close(fd_in);
}

static void	append_redir(t_simple_cmd *cmd)
{
	int	fd_out;

	if (!cmd->output_path_append)
		return ;
	fd_out = open(cmd->output_path_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->output_path_append, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(1);
	}
	cmd->saved_stdout = dup(STDOUT_FILENO);
	if (cmd->saved_stdout == -1)
	{
		close(fd_out);
		exit(1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		close(fd_out);
		close(cmd->saved_stdout);
		exit(1);
	}
	close(fd_out);
}

static void	out_redir(t_simple_cmd *cmd)
{
	int	fd_out;

	if (!cmd->output_path)
		return ;
	fd_out = open(cmd->output_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->output_path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(1);
	}
	cmd->saved_stdout = dup(STDOUT_FILENO);
	if (cmd->saved_stdout == -1)
	{
		close(fd_out);
		exit(1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		close(fd_out);
		close(cmd->saved_stdout);
		exit(1);
	}
	close(fd_out);
}
/*static int open_heredoc(void)
{
    int fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        ft_putstr_fd("Error: failed to open heredoc file\n", 2);
    return (fd);
}

// Zapisuje dane wejściowe do pliku heredoc
static void write_to_heredoc(int fd, char *input)
{
    if (write(fd, input, ft_strlen(input)) < 0 || write(fd, "\n", 1) < 0)
        ft_putstr_fd("Error: failed to write to heredoc file\n", 2);
}

// Główna funkcja heredoc
static void heredoc_redir(t_simple_cmd *cmd)
{
    int     fd;
    char    *input;

    fd = open_heredoc_file();
    if (fd < 0)
        exit(1);
    // Pobieranie danych od użytkownika aż do napotkania delimitera
    while (1)
    {
        input = readline("> ");
        if (!input)
        {
            ft_putstr_fd("Error: readline failed\n", 2);
            close(fd);
            exit(1);
        }
        // Sprawdzanie, czy wpisany tekst to delimiter
        if (ft_strncmp(input, cmd->delimiter_heredoc, ft_strlen(cmd->delimiter_heredoc)) == 0)
        {
            free(input);
            break;
        }
        write_to_heredoc_file(fd, input);
        free(input);
    }
    close(fd);
}*/
static void	heredoc_redir(t_simple_cmd *cmd)
{
	int		fd;
	char	*input;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Error: failed to open heredoc file\n", 2);
		exit(1);
	}
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			ft_putstr_fd("Error: readline failed\n", 2);
			close(fd);
			exit(1);
		}
		if (ft_strncmp(input, cmd->delimiter_heredoc,
				ft_strlen(cmd->delimiter_heredoc)) == 0)
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
		free(input);
	}
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: failed to open heredoc file for reading\n", 2);
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Error: failed to duplicate file descriptor\n", 2);
		close(fd);
		exit(1);
	}
	close(fd);
	unlink(".heredoc");
}

int	redir_check(t_simple_cmd *cmd)
{
	if (!cmd)
		return (-1);
	cmd->saved_stdin = -1;
	cmd->saved_stdout = -1;
	if (cmd->input_path)
		in_redir(cmd);
	if (cmd->output_path)
		out_redir(cmd);
	if (cmd->output_path_append)
		append_redir(cmd);
	if (cmd->heredoc)
		heredoc_redir(cmd);
	return (0);
}

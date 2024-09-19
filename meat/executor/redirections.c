/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:30:42 by astefans          #+#    #+#             */
/*   Updated: 2024/09/18 14:30:51 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void		in_redir(t_simple_cmd *cmd)
{
	int fd_in;

	fd_in = open(cmd->input_path, O_RDONLY);
	if (cmd->input_path)
	{
		if (fd_in < 0)
		{
			return (ft_putstr_fd("Filed to handle a file\n", 2));
		}
	}
	dup2(fd_in, STDIN_FILENO);
	free(cmd->input_path);
	close(fd_in);
}

static void		out_redir(t_simple_cmd *cmd)
{
	int fd_out;

	fd_out = open(cmd->output_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->output_path)
	{
		if (fd_out < 0)
		{
			return (ft_putstr_fd("Filed to handle a file\n", 2));
		}
	}
	dup2(fd_out, STDOUT_FILENO);
	free(cmd->output_path);
	close(fd_out);
}

static void		append_redir(t_simple_cmd *cmd)
{
	int fd_out;

	fd_out = open(cmd->output_path_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->output_path_append)
	{
		if (fd_out < 0)
		{
			return (ft_putstr_fd("Filed to handle a file\n", 2));
		}
	}
	dup2(fd_out, STDOUT_FILENO);
	free(cmd->output_path_append);
	close(fd_out);
}

static void		heredoc_redir(t_simple_cmd *cmd)
{
	int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
    {
        return (ft_putstr_fd("Pipe creation failed\n", 2));
    }

    // Zapisujemy dane heredoc do potoku
    write(pipe_fd[1], cmd->delimiter_heredoc, ft_strlen(cmd->delimiter_heredoc));
    close(pipe_fd[1]);  // Zamykanie końca do zapisu po zapisaniu danych

    // Przekierowujemy stdin na potok
    dup2(pipe_fd[0], STDIN_FILENO);  // Przekierowanie stdin na dane heredoc
    close(pipe_fd[0]); 
}

void redir_check(t_simple_cmd *cmd)
{
	if (cmd->output_path)
		out_redir(cmd);
	else if  (cmd->input_path)
		in_redir(cmd);
	else if (cmd->output_path_append)
		append_redir(cmd);
	else if (cmd->heredoc)
		heredoc_redir(cmd);
}
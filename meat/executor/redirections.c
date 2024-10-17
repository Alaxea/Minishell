/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:30:42 by astefans          #+#    #+#             */
/*   Updated: 2024/10/17 23:16:53 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void		in_redir(t_simple_cmd *cmd)
{
	int fd_in;

	fd_in = 0;
	if (cmd->input_path)
	{
		fd_in = open(cmd->input_path, O_RDONLY);
		if (fd_in < 0)
		{
			(ft_putstr_fd("Filed to handle a file\n", 2));
			return;
		}
	}
	dup2(fd_in, STDIN_FILENO);
	free(cmd->input_path);
	close(fd_in);
}

static void		out_redir(t_simple_cmd *cmd)
{
	int fd_out;

	fd_out = 0;
	if (cmd->output_path)
	{
		fd_out = open(cmd->output_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < -1)
		{
			(ft_putstr_fd("Filed to handle a file\n", 2));
			return;
		}
		dup2(fd_out, STDOUT_FILENO);
		free(cmd->output_path);
		close(fd_out);
	}
}

static void		append_redir(t_simple_cmd *cmd)
{
	int fd_out;

	fd_out = 0;
	if (cmd->output_path_append)
	{
		fd_out = open(cmd->output_path_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_out < 0)
		{
			(ft_putstr_fd("Filed to handle a file\n", 2));
			return;
		}
	}
	dup2(fd_out, STDOUT_FILENO);
	free(cmd->output_path_append);
	close(fd_out);
}

static void		heredoc_redir(t_simple_cmd *cmd)
{
	int	fd;
	char *input;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        ft_putstr_fd("Error: failed to open heredoc file\n", 2);
        return;
    }
	while (1)
	{
		input = readline("> ");
		if (!input)
        {
            ft_putstr_fd("Error: readline failed\n", 2);
            break;
        }
		if (ft_strncmp(input, cmd->delimiter_heredoc, ft_strlen(input)) == 0)
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
        return;
    }
    dup2(fd, STDIN_FILENO);
	close(fd);
}

void redir_check(t_simple_cmd *cmd)
{
	int i = 0;
    int arg_count = 0;

    while (cmd->cmd[arg_count] != NULL)
    {
        arg_count++;
    }

    // Alokacja pamięci dla argumentów
    cmd->cmd = malloc((arg_count + 1) * sizeof(char *));
    if (!cmd->cmd)
    {
        perror("malloc failed");
        return;
    }
    while (cmd->cmd[i])
    {
        if (ft_strncmp(cmd->cmd[i], ">", 1) == 0)
        {
            out_redir(cmd);
        }
        else if (ft_strncmp(cmd->cmd[i], "<", 1) == 0)
        {
            in_redir(cmd);
        }
        else if (ft_strncmp(cmd->cmd[i], ">>", 2) == 0)
        {
            append_redir(cmd);
        }
        else if (ft_strncmp(cmd->cmd[i], "<<", 2) == 0)
        {
            heredoc_redir(cmd);
        }
        i++;
    }
    // Zwalnianie pamięci
    i = 0; 
    while (cmd->cmd[i])
    {
        free(cmd->cmd[i]); // Zwalnianie pojedynczego argumentu
        i++;
    }
    free(cmd->cmd); // Zwalnianie tablicy wskaźników
    cmd->cmd = NULL;
}

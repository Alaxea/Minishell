/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:30:42 by astefans          #+#    #+#             */
/*   Updated: 2024/11/12 16:41:48 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_readline_error(char *input, int fd, char *error_msg)
{
	if (!input)
	{
		ft_putstr_fd(error_msg, 2);
		close(fd);
		exit(1);
	}
}

static void	write_and_free_input(char *input, int fd)
{
	ft_putstr_fd(input, fd);
	ft_putstr_fd("\n", fd);
	free(input);
}

static void	handle_dup2_error(int fd, char *error_msg)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putstr_fd(error_msg, 2);
		close(fd);
		exit(1);
	}
}

static void	read_and_write_heredoc(int fd, t_simple_cmd *cmd)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		handle_readline_error(input, fd, "Error: readline failed\n");
		if (ft_strncmp(input, cmd->delimiter_heredoc,
				ft_strlen(cmd->delimiter_heredoc)) == 0)
		{
			free(input);
			break ;
		}
		write_and_free_input(input, fd);
	}
}

void	heredoc_redir(t_simple_cmd *cmd)
{
	int	fd;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	handle_open_error(fd, "Error: failed to open heredoc file\n");
	read_and_write_heredoc(fd, cmd);
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	handle_open_error(fd, "Error: failed to open heredoc file for reading\n");
	handle_dup2_error(fd, "Error: failed to duplicate file descriptor\n");
	close(fd);
	unlink(".heredoc");
}

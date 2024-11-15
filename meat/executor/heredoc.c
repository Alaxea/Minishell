/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:30:42 by astefans          #+#    #+#             */
/*   Updated: 2024/11/15 16:51:41 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		if (!input)
		{
			ft_putstr_fd("minishell: warning: here-document\
delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(cmd->delimiter_heredoc, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
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

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	handle_open_error(fd, "Error: failed to open heredoc file\n");
	read_and_write_heredoc(fd, cmd);
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	handle_open_error(fd, "Error: failed to open heredoc file for reading\n");
	handle_dup2_error(fd, "Error: failed to duplicate file descriptor\n");
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(".heredoc");
}

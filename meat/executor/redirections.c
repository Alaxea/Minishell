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
	int	fd;
	char *input;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		input = readline("> ");
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
	fd = open(".heredoc", O_RDONLY, 0644);
	dup2(fd, 0);
	free(cmd->delimiter_heredoc);
	cmd->delimiter_heredoc = NULL;
	close(fd);
}

void redir_check(t_simple_cmd *cmd)
{
	if (cmd->output_path)
		out_redir(cmd);
	else if  (cmd->input_path)
		in_redir(cmd);
	else if (cmd->output_path_append)
		append_redir(cmd);
	else if (cmd->delimiter_heredoc)
		heredoc_redir(cmd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:30:42 by astefans          #+#    #+#             */
/*   Updated: 2024/10/02 17:13:05 by zogorzeb         ###   ########.fr       */
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
	// dup2(fd_in, STDIN_FILENO);
	// free(cmd->input_path);
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
	// dup2(fd_out, STDOUT_FILENO);
	// free(cmd->output_path);
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
	// dup2(fd_out, STDOUT_FILENO);
	// free(cmd->output_path_append);
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
	int i;

	i = 0;
	while (cmd->arguments && cmd->arguments[i])
	{
		if (cmd->arguments == NULL)
	{
		ft_putstr_fd("minishell: syntax error ", STDERR_FILENO);
		ft_putstr_fd("near unexpected token `newline'\n", STDERR_FILENO);
		//last result?
		return (0);
	}
		if (ft_strncmp(cmd->arguments[i], ">", 1) == 0)
		{
			out_redir(cmd);
			break ;
		}
		else if  (ft_strncmp(cmd->arguments[i], "<", 1) == 0)
		{
			in_redir(cmd);
			break ;
		}
		else if (ft_strncmp(cmd->arguments[i], ">>", 2) == 0)
		{
			append_redir(cmd);
			break ;
		}
		else if (ft_strncmp(cmd->arguments[i], "<<", 2) == 0)
		{
			heredoc_redir(cmd);
			break ;
		}
	}
	i++;
}
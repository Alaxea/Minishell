/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:09:56 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/07/26 14:41:25 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	get_next_line_loop(char *limiter, int heredoc_fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(limiter, line, (size_t)(ft_strlen_gnl(line) - 1)) == 0)
		{
			free(line);
			break ;
		}
		write(heredoc_fd, line, ft_strlen_gnl(line));
		free(line);
	}
}

void	heredoc(char *limiter, char **argv, t_pipex_data *data)
{
	int		heredoc_fd;

	heredoc_fd = open(".heredoc.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd < 0)
		return_error("open() error");
	get_next_line_loop(limiter, heredoc_fd);
	close(heredoc_fd);
	data->infile_fd = open(".heredoc.txt", O_RDONLY);
	if (dup2(data->infile_fd, data->array_of_pipes[0][0]) == -1)
		return_error("dup2() error");
	data->outfile_fd = open(argv[data->argc - 1],
			O_WRONLY | O_CREAT | O_APPEND);
	if (data->outfile_fd < 0)
		return_error("open() error");
	if (dup2(data->outfile_fd,
			data->array_of_pipes[data->num_of_pipes - 1][1]) == -1)
		return_error("dup2() error");
	close(data->outfile_fd);
	close(data->infile_fd);
}

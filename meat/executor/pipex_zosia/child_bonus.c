/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:09:40 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/10/09 16:46:01 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../../../minishell.h"

static void	child_closing_pipes(t_pipex_data *p_data)
{
	int	input;
	int	i;
	int	output;

	i = 0;
	input = p_data->c_pos;
	output = p_data->c_pos + 1;
	while (i < p_data->num_of_pipes)
	{
		if (i != input)
		{
			if (close(p_data->array_of_pipes[i][0]) == -1)
				return_error("close input error");
		}
		if (i != output)
		{
			if (close(p_data->array_of_pipes[i][1]) == -1)
				return_error("close output error");
		}
		i++;
	}
}

/*int	child(char **argv, t_pipex_data *p_data)
{
	int	output;
	int	input;

	input = p_data->c_pos;
	output = input + 1;
	child_closing_pipes(p_data);
	dup2(p_data->array_of_pipes[input][0], STDIN_FILENO);
	dup2(p_data->array_of_pipes[output][1], STDOUT_FILENO);
	redir_check();
	close(p_data->array_of_pipes[input][0]);
	close(p_data->array_of_pipes[output][1]);
	exec_prep(p_data, argv[p_data->c_pos + 2 + p_data->heredoc], p_data->envp);
	return (EXIT_SUCCESS);
}*/

int	child(char **argv, t_pipex_data *p_data)
{
	int	output;
	int	input;

	input = p_data->c_pos;
	output = input + 1;
	child_closing_pipes(p_data);
	redir_check(cmd);
	dup2(p_data->array_of_pipes[input][0], STDIN_FILENO);
	dup2(p_data->array_of_pipes[output][1], STDOUT_FILENO);
	close(p_data->array_of_pipes[input][0]);
	close(p_data->array_of_pipes[output][1]);
	exec_prep(p_data, argv[p_data->c_pos + 2 + p_data->heredoc], p_data->envp);
	return (EXIT_SUCCESS);
}

/*void	open_files(t_pipex_data *data, char **argv)
{
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_fd < 0)
		return_error("open() error");
	dup2(data->infile_fd, data->array_of_pipes[0][0]);
	data->outfile_fd = open(argv[data->argc - 1], O_RDWR | O_CREAT | O_TRUNC);
	if (data->outfile_fd < 0)
		return_error("open() error");
	dup2(data->outfile_fd, data->array_of_pipes[data->num_of_pipes - 1][1]);
	close(data->outfile_fd);
	close(data->infile_fd);
}*/

void	open_files(t_pipex_data *data, char **argv)
{
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_fd < 0)
		return_error("open() error");
	dup2(data->infile_fd, STDIN_FILENO);
	data->outfile_fd = open(argv[data->argc - 1], O_RDWR | O_CREAT | O_TRUNC);
	if (data->outfile_fd < 0)
		return_error("open() error");
	dup2(data->outfile_fd, STDOUT_FILENO);
	close(data->outfile_fd);
	close(data->infile_fd);
}
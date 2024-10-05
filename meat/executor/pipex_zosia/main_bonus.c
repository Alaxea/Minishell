/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:10:02 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/10/03 14:06:00 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	parent_process(t_pipex_data *p_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < p_data->num_of_pipes)
	{
		j = 0;
		while (j < 2)
		{
			if (i == p_data->num_of_pipes - 1 && j == 1)
				j++;
			else
				close(p_data->array_of_pipes[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < p_data->num_of_processes)
	{
		if (wait(NULL) == -1)
			return_error("wait error");
		i++;
	}
	close(p_data->array_of_pipes[p_data->num_of_pipes - 1][1]);
}

void	pipex_init(t_pipex_data *data)
{
	int	i;

	i = 0;
	data->c_pos = -1;
	data->paths = find_paths(data->envp);
	data->num_of_pipes = data->num_of_processes + 1;
	data->array_of_pipes = (int **)malloc(data->num_of_pipes * sizeof(int *));
	if (data->array_of_pipes == NULL)
		return_error("malloc() error");
	while (i < data->num_of_pipes)
	{
		data->array_of_pipes[i] = malloc(2 * sizeof(int));
		if (!(data->array_of_pipes[i]))
		{
			while (--i >= 0)
				free(data->array_of_pipes[i]);
			free(data->array_of_pipes);
			return_error("malloc() error");
		}
		pipe(data->array_of_pipes[i]);
		i++;
	}
}

static void	cleanup(t_pipex_data *pipex_d)
{
	int	i;

	i = 0;
	free_array(pipex_d->paths);
	while (i < pipex_d->num_of_pipes)
	{
		free(pipex_d->array_of_pipes[i]);
		i++;
	}
	free(pipex_d->array_of_pipes);
}
void	handle_pipe(t_simple_cmd *current)


int	pipex(t_data *data)
{
	int	pid;
	t_pipex_data *pipex;

	pipex_init(pipex);
	while (++(pipex_d->c_pos) < pipex_d->num_of_processes)
	{
		pid = fork();
		if (pid == -1)
			return_error("fork() error");
		if (pid == 0)
			child(data->argv, pipex_d);
	}
	parent_process(pipex_d);
	cleanup(pipex_d);
	if (pipex_d->heredoc == 1)
		unlink(".heredoc.txt");
	return (EXIT_SUCCESS);
}

// 		pipex_data.num_of_processes = argc - 3 - pipex_data.heredoc; 	OK
// 		pipex_init(&pipex_data);	OK	


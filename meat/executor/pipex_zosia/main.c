/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:45:35 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/07/26 16:39:19 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(char **argv, char **envp, t_pipex *data)
{
	pid_t	pid1;
	pid_t	pid2;

	data->file1 = open(argv[1], O_RDONLY);
	if (data->file1 == -1)
		error("open infile error", data);
	data->file2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (pipe(data->fd) == -1)
		return_error("pipe() error");
	pid1 = fork();
	if (pid1 == 0)
		child_routine_infile(argv, *data, envp);
	pid2 = fork();
	if (pid2 == 0)
		child_routine_outfile(argv, *data, envp);
	close(data->fd[0]);
	close(data->fd[1]);
	if (waitpid(pid1, NULL, 0) == -1)
		return_error("waitpid1 error");
	if (waitpid(pid2, NULL, 0) == -1)
		return_error("waitpid2 error");
	close(data->file1);
	close(data->file2);
	free_array(data->paths);
	return (EXIT_SUCCESS);
}

static void	check_commands(char **argv, int argc, char **paths)
{
	int	i;
	char	**cmds;
	char	*cmd;

	i = 2;
	while (i < argc - 1)
	{
		cmds = ft_split(argv[i], ' ');
		cmd = find_the_proper_path(cmds[0], paths);
		if (!cmd)
		{
			free_array(paths);
			free_array(cmds);
			exit (EXIT_FAILURE);
		}
		else
		{
			free(cmd);
			free_array(cmds);
			i++;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc != 5)
	{
		write(2, "there should be 4 arguments\n", 29);
		return (EXIT_FAILURE);
	}
	else
	{	
		if (access(argv[1], O_RDONLY) == -1)
		{
			perror("open() error");
			exit(1);
		}
		data.paths = find_paths(envp);
		check_commands(argv, argc, data.paths);
		pipex(argv, envp, &data);
	}
	return (EXIT_SUCCESS);
}

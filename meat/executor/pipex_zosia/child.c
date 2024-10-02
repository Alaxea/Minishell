/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:44:51 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/07/26 16:15:40 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_routine_infile(char **argv, t_pipex data, char **envp)
{
	close(data.fd[0]);
	if (dup2(data.file1, STDIN_FILENO) == -1)
		return_error("dup2 problem");
	if (dup2(data.fd[1], STDOUT_FILENO) == -1)
		return_error("dup2 problem");
	close(data.fd[1]);
	close(data.file2);
	close(data.file1);
	if (exec_prep(data, argv[2], envp) == 1)
		return_error("error");
}

void	child_routine_outfile(char **argv, t_pipex data, char **envp)
{
	close(data.fd[1]);
	if (dup2(data.fd[0], STDIN_FILENO) == -1)
		return_error("dup2 problem");
	if (dup2(data.file2, STDOUT_FILENO) == -1)
		return_error("dup2 problem");
	close(data.fd[0]);
	close(data.file2);
	close(data.file1);
	if (exec_prep(data, argv[3], envp) == 1)
		return_error("error");
}

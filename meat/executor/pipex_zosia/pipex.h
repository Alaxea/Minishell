/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:45:45 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/07/26 16:18:58 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <stddef.h>

typedef struct t_pipex
{
	int		file1;
	int		file2;
	int		fd[2];
	char	**paths;
	char	**commands;
	char	*proper_path;
}	t_pipex;
// -------------- PIPEX -----------------
void	child_routine_infile(char **argv, t_pipex data, char **envp);
void	child_routine_outfile(char **argv, t_pipex data, char **envp);
int		exec_prep(t_pipex data, char *command, char **envp);
char	**find_paths(char **envp);
char	*find_the_proper_path(char *command, char **paths);
int		pipex(char **argv, char **envp, t_pipex *data);
void	return_error(char *message);
void	free_array(char **array);
void	error(char *message, t_pipex *data);
// -------------- LIBFT -----------------
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char *str, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
// -------------- GET_NEXT_LINE ------------
char	*ft_strdup(char *str1);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	*ft_newline(char **buffer);
char	*ft_strjoin_new(char *buffer, char *new_s);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen_new(char *str);
char	*write_to_buffer(char *buffer, int fd);
#endif

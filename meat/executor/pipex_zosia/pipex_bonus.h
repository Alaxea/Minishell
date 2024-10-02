/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:39:48 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/10/02 14:56:12 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

# define BUFFER_SIZE 100

typedef struct s_pipex_data
{
	int		num_of_processes;
	int		**array_of_pipes;
	int		c_pos;
	int		num_of_pipes;
	int		heredoc;
	int		argc;
	char	**envp;
	int		infile_fd;
	int		outfile_fd;
	char	**paths;
}	t_pipex_data;
// -------------- GET_NEXT_LINE ------------
char	*ft_strdup_gnl(char *str1);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	*ft_newline(char **buffer);
char	*ft_strjoin_gnl(char *buffer, char *new_s);
char	*ft_strchr_gnl(const char *str, int c);
size_t	ft_strlen_gnl(char *str);
char	*write_to_buffer(char *buffer, int fd);
// --------------- PIPEX ----------------------
void	pipex_init(t_pipex_data *data);
void	error(char *message, t_pipex_data *data);
int		exec_prep(t_pipex_data *data, char *command, char **envp);
void	return_error(char *message);
int		pipex(char **argv, t_pipex_data *pipex_d);
char	**ft_split(const char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	heredoc(char *limiter, char **argv, t_pipex_data *data);
void	get_next_line_loop(char *limiter, int heredoc_fd);
int		child(char **argv, t_pipex_data *p_data);
char	**find_paths(char **envp);
size_t	ft_strlen(const char *str);
void	free_array(char **array);
void	open_files(t_pipex_data *data, char **argv);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:02:29 by astefans          #+#    #+#             */
/*   Updated: 2024/11/22 11:54:07 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes/libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

# define BUFFER_SIZE 42

typedef enum s_redir_type
{
	STANDARD,
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	PIPE
}	t_redir_type;

typedef enum s_node_type
{
	COMMAND_NODE,
	PIPE_NODE,
}	t_node_type;

typedef enum s_quote_mode
{
	DEFAULT,
	SINGLE_Q,
	DOUBLE_Q
}	t_quote_mode;

typedef enum s_type
{
	WORD,
	OPERATOR
}	t_type;

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	char			*value;
	t_redir_type	data_type;
}	t_token;

typedef struct s_io_fds
{
	struct s_simple_cmd	*command;
	char				*infile;
	char				*outfile;
	int					fd_in;
	int					fd_out;
}	t_io_fds;

typedef struct s_simple_cmd
{
	int					fd_out;
	int					fd_in;
	char				*name;
	char				**cmd;
	char				*path;
	char				*output_path;
	char				*output_path_append;
	char				*input_path;
	char				*delimiter_heredoc;
	bool				heredoc;
	bool				parser_done;
	int					saved_stdin;
	int					saved_stdout;
	pid_t				pid;
	struct s_simple_cmd	*next;
	struct s_simple_cmd	*prev;
}	t_simple_cmd;

typedef struct s_data
{
	char			*input;
	t_token			*tokens;
	t_simple_cmd	*simple_cmds;
	char			**envp;
	char			**env_var;
	t_io_fds		fd_out;
	int				last_result;
	int				fd[2];
}	t_data;

int				ft_iswhitespace(char c);
void			ft_lstadd_back(t_token **lst, t_token *new);
void			ft_lstadd_front(t_token **lst, t_token *new);
void			ft_lstclear(t_token **lst);
void			ft_lstdelone(t_token *lst);
t_token			*ft_lstlast(t_token *lst);
t_token			*ft_lstnew(void *content, t_redir_type type);
int				ft_lstsize(t_token *lst);
void			token_error(t_token **token, char *message);
int				validation(t_token **token);
t_token			*token_creator(char *input, int i, int start);
t_simple_cmd	*simple_cmd_creator(t_token *token);
void			check_quote(t_quote_mode *mode, char c);
char			**ft_split_quotes(char *str, char c);
char			*trim_the_value(char *old);
char			*cut_out_path(char *value);
void			redir_modify(t_token *token,
					t_simple_cmd *simple_cmd, t_redir_type type);
t_simple_cmd	*parser(t_token *tokens);
char			*replace_env(char *str, char **env);
int				expand(t_simple_cmd *cmds, char **env, t_data *data);
char			*double_quotes_env(char *str, char **env,
					int *start, int *stop);
char			*trim_quotes(char *command);
void			path_expander(t_simple_cmd *cmds, char **env);
int				cmd_validation(t_data *data, t_simple_cmd *cmds, char **env);
int				is_cmd_valid(t_simple_cmd *cmds, char **env);
char			*find_env_var(char *str, int *start, int *stop);
size_t			ft_len_until_eq_sign(char *env);
char			*get_env(char **env, char *var);
void			replace_with_exit_status(t_simple_cmd *sc, t_data *data);
char			**ft_split_quotes(char *str, char c);
char			**ft_check_str(char *str, char c, t_quote_mode *mode);
/*EXECUTOR PART*/
/*env_helper*/
void			copy_env_var(t_data *env, char **env_var);
char			*set_env_var(t_data *env, char *name);
void			add_env_var(t_data *env, char *name, char *value);
void			delete_env_var(t_data *env, char *name);
/*clean*/
void			clear_tab(char **tab);
void			clear_env(t_data *env);
void			exit_shell(t_data *env, char *mess, int fail);
void			free_simple_cmd(t_simple_cmd *cmd);
/*builtins*/
int				cd_builtin(t_data *env, t_simple_cmd *cmd);
int				echo_builtin(t_simple_cmd *cmd);
void			print_tab(char **tab, int fd_out);
int				env_builtin(t_data *env, t_simple_cmd *cmd);
int				exit_builtin(t_data *env, t_simple_cmd *cmd);
int				export_builtin(t_data *env, t_simple_cmd *cmd);
int				pwd_builtin(t_data *data, t_simple_cmd *cmd);
int				unset_builtin(t_data *env, t_simple_cmd *cmd);
int				check_for_builtins(t_simple_cmd *sc);
int				execute_builtin(t_data *data, t_simple_cmd *cmd);
int				is_builtin(t_data *command, int fd);
void			clean_builtin(t_data *data);
/*exec_path*/
char			*concat_path(const char *dir, const char *command);
char			*get_full_path(const char *command, char **envp);
int				check_permission(struct stat file);
int				find_binary(t_data *env, t_simple_cmd *cmd,
					char *bin_path, char **path);
int				execute_path(char *bin_path, t_data *env, t_simple_cmd *cmd);
char			*get_env_var(const char *var_name, char **envp);
int				execute_command(t_simple_cmd *cmd, char **envp);
int				check_for_builtins(t_simple_cmd *sc);
char			*find_script(char *script, t_data *env);
int				search_in_path(t_data *env, t_simple_cmd *cmd);
void			free_paths(char **paths);
/*pipes*/
void			close_pipes(t_simple_cmd *cmd);
int				create_pipes(t_data *env, t_simple_cmd *cmd);
int				fork_and_execute(t_simple_cmd *cmd, t_data *env);
int				execute(t_simple_cmd *cmd, t_data *env);
void			setup_redirection(t_simple_cmd *current);
/*redirection*/
int				redir_check(t_simple_cmd *cmd);
void			heredoc_redir(t_simple_cmd *cmd);
/*signals*/
void			handle_sigquit(int signal);
void			handle_sigint(int signal);
void			setup_signals(void);
void			ignore_signals(void);
void			default_signals(void);
/*utils*/
void			handle_open_error(int fd, char *error_msg);
int				error_command_not_found(void);
void			clean_data(t_data *data);
/*main*/
int				parsing(t_data *data);
int				executing(t_data *data);
int				minishell(t_data *data);
#endif

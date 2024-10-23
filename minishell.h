#ifndef MINISHELL_H
# define MINISHELL_H

#include "includes/libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

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

# define BUFFER_SIZE 42
typedef enum	s_redir_type
{
	STANDARD,
	REDIR_INPUT, // < //
	REDIR_OUTPUT, // > //
	REDIR_APPEND, // >> //
	REDIR_HEREDOC, // << - specific mode //
	PIPE
}	t_redir_type;

typedef	enum	s_node_type
{
	COMMAND_NODE,
	PIPE_NODE,
}	t_node_type;

typedef enum	s_quote_mode
{
	DEFAULT,
	SINGLE_Q,
	DOUBLE_Q
}	t_quote_mode;

typedef enum	s_type
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
	struct s_simple_cmd *command;
	char *infile;
	char *outfile;
	int		fd_in;
	int		fd_out;
}   t_io_fds;

typedef struct s_simple_cmd
{
	int				fd_out;
	int				fd_in;
	char			*name; // basically a pathname for the execve
	char			**cmd; // argv array for execve
	char			*flags;
	char			*path;
	char			*output_path;
	char			*output_path_append;
	char			*input_path;
	char			*delimiter_heredoc;
	bool			heredoc;
	bool			parser_done;
	pid_t pid;
	char	*command;
	struct s_simple_cmd	*next;
	struct s_simple_cmd	*prev;
	struct s_data *data;
	t_io_fds		*io_fds;
}	t_simple_cmd;

typedef struct s_data
{
	char		*input;
	//char		*current_dir;
	//char		*old_dir;
	t_token		*tokens;
	t_simple_cmd	*simple_cmds;
	char	**envp;
	char	**env_var;
	bool	interactive;
	t_simple_cmd	*cmd;
	t_token	*token;
	t_io_fds fd_out;
	int exit_code;
	int last_result; //do pipes.c
	int fd[2]; //do pipes.c;
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
t_token			*token_creator(char *input);
t_simple_cmd	*simple_cmd_creator(t_token *token);
void			check_quote(t_quote_mode *mode, char c);
char			**ft_split_quotes(char *str, char c);
char			*trim_the_value(char *old);
char			*cut_out_path(char *value);
void			error(void);
t_simple_cmd	*parser(t_token *tokens);
char			*replace_env(char *str, char **env);
int				expand(t_simple_cmd *cmds, char **env);
char			*double_quotes_env(char *str, char **env);
void			print_tab(char **tab, int fd_out);
int				env_builtin(t_data *env, t_simple_cmd *cmd);
//int	echo(char **args, int argc, int fd);
int				is_builtin(t_data *command, int fd);
void			clear_tab(char **tab);
void			clear_env(t_data *env);
void			copy_env_var(t_data *env, char **env_var);
char			*set_env_var(t_data *env, char *name);
void			add_env_var(t_data *env, char *name, char *value);
void			delete_env_var(t_data *env, char *name);
int				pwd_builtin(t_data *data, t_simple_cmd *cmd);
int				echo_builtin(t_simple_cmd *cmd);
int				check_for_builtins(t_simple_cmd *sc);
int				execute_builtin(t_data *data, t_simple_cmd *cmd);
int				cd_builtin(t_data *env, t_simple_cmd *cmd);
int				exit_builtin(t_data *env, t_simple_cmd *cmd);
int				export_builtin(t_data *env, t_simple_cmd *cmd);
int				unset_builtin(t_data *env, t_simple_cmd *cmd);
char *get_full_path(const char *command, char **envp);
void 			redir_check(t_simple_cmd *cmd);
char *trim_quotes(char *command);
char *find_env_var(char *str, int *start, int *stop);
int	cmd_validation(t_simple_cmd *cmds, char **env);
char	**find_paths(char **envp);
int	is_cmd_valid(t_simple_cmd *cmds, char **env);
void	path_expander(t_simple_cmd *cmds, char **env);
int execute_command(t_simple_cmd *cmd, char **envp);
int     check_permission(struct stat file);
size_t	ft_len_until_eq_sign(char *env);
char	*get_env(char **env, char *var);
int	check_for_builtins(t_simple_cmd *sc);
void	redir_builtin(t_simple_cmd *cmd);
void	exit_shell(t_data *env, char *mess, int fail);
char	*find_script(char *script, t_data *env);
int	search_in_path(t_data *env, t_simple_cmd *cmd);
int	find_binary(t_data *env, t_simple_cmd *cmd, char *bin_path, char **path);
int	execute_path(char *bin_path, t_data *env, t_simple_cmd *cmd);
char *concat_path(const char *dir, const char *command);
char  **allocate_arguments(t_simple_cmd *cmd, int count);
void free_arguments(char **arguments);
char    **ft_dup_envp(char **envp);
void    ft_free_envp(char **envp);
int	is_valid_env_var(const char *key_value);


/*pipes*/

/*void	handle_pipe(t_simple_cmd *current);
void	create_pipes(t_simple_cmd *commands, t_data *env);
void	close_fds_main(t_simple_cmd *commands);
void	close_fds_child(t_simple_cmd *commands, int i);
int		waiting_and_result(t_simple_cmd *commands, t_data *env);
void	fork_child(t_data *env, t_simple_cmd *commands, int i);
void	close_pipes(t_simple_cmd *hell);
void	execute(t_data *data, t_simple_cmd *cmd);*/

void close_pipes(t_simple_cmd *cmd);
int create_pipes(t_data *env, t_simple_cmd *cmd);
int fork_and_execute(t_simple_cmd *cmd, t_data *env);
int execute(t_simple_cmd *cmd, t_data *env);

/*signals*/
void handle_sigquit(int signal);
void handle_sigint(int signal);
void	signals(void);

#endif
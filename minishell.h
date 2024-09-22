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
	char *infile;
	char *outfile;
	int		fd_in;
	int		fd_out;
}   t_io_fds;

typedef struct s_simple_cmd
{
	char			*name; // basically a pathname for the execve
	char			**cmd; // argv array for execve
	char			*command;
	char			*flags;
	char			**arguments;
	char			*path;
	char			*output_path;
	char			*output_path_append;
	char			*input_path;
	char			*delimiter_heredoc;
	bool			heredoc;
	bool			parser_done;
	struct s_simple_cmd	*next;
	struct s_simple_cmd	*prev;
	t_io_fds		*io_fds;
}	t_simple_cmd;

typedef struct s_data
{
	char		*input;
	char		*current_dir;
	char		*old_dir;
	t_token		*tokens;
	t_simple_cmd	*simple_cmds;
	char	**envp;
	char	**env_var;
	bool	interactive;
	t_simple_cmd	*cmd;
	t_token	*token;
	t_io_fds fd_out;
	char	*command;
	int exit_code;
}	t_data;

int				ft_iswhitespace(char c);
void			ft_lstadd_back(t_token **lst, t_token *new);
void			ft_lstadd_front(t_token **lst, t_token *new);
void			ft_lstclear(t_token **lst);
void			ft_lstdelone(t_token *lst);
t_token			*ft_lstlast(t_token *lst);
t_token			*ft_lstnew(void *content, t_redir_type type);
int				ft_lstsize(t_token *lst);
void			handle_sigquit(int sig);
void			handle_sigint(int sig);
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
void			print_tab(char **tab);
int				env_builtin(t_data *env);
//int	echo(char **args, int argc, int fd);
int				is_builtin(t_data *command, int fd);
void			clear_tab(char **tab);
void			clear_env(t_data *env);
void			copy_env_var(t_data *env, char **env_var);
char			*set_env_var(t_data *env, char *name);
void			add_env_var(t_data *env, char *name, char *value);
void			delete_env_var(t_data *env, char *name);
int				pwd_builtin(t_data *data);
int				echo_builtin(t_simple_cmd *com);
int				check_for_builtins(t_simple_cmd *sc);
int				execute_builtin(t_data *data);
int				cd_builtin(t_data *env, t_simple_cmd com);
int				exit_builtin(t_data *env, t_simple_cmd com);
int				export_builtin(t_data *env, t_simple_cmd com);
int				unset_builtin(t_data *env, t_simple_cmd com);
char *get_full_path(const char *command, char **envp);
void redir_check(t_simple_cmd *cmd);
char *trim_quotes(char *command);
char *find_env_var(char *str, int *start, int *stop);
char	*get_env(char **env, char *var);
int	cmd_validation(t_simple_cmd *cmds, char **env);
char	**find_paths(char **envp);

#endif
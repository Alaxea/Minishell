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

#ifndef PATH_MAX
# define PATH_MAX 4096 /*pełna ścieżka do pliku, wliczając w to katalogi i nazwę pliku, w linux*/
#endif

typedef struct	s_io_fd
{
	int	input;
	int	output;
	int heredoc;
}	t_io_fd;


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


typedef struct s_simple_cmd
{
	char			*name;
	char			**cmd;
	char			*path;
	char			*output_path;
	char			*output_path_append;
	char			*input_path;
	char			*delimiter_heredoc;
	bool			heredoc;
	bool			parser_done;
	
}	t_simple_cmd;

typedef struct s_data
{
	char		*current_dir;
	char		*old__dir;
	char		**env;
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
int				pwd_builtin(t_data *data, char **args);
void			error(void);
int				env_builtin(t_data *data, char **args);

#endif
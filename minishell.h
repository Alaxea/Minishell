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

typedef struct	s_io_fd
{
	int	input;
	int	output;
	int heredoc;
}	t_io_fd;


typedef enum	s_redir_type
{
	DEFAULT,
	REDIR_INPUT, // < //
	REDIR_OUTPUT, // > //
	REDIR_APPEND, // >> //
	REDIR_HEREDOC // << - specific mode //
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
	int				data_type;
}	t_token;


typedef struct s_simple_cmd
{
	char			*name;
	char			**cmd;
	char			*path;
	t_redir_type	redir_type;
	char			*input_file;
	char			*output_file;
}	t_simple_cmd;


typedef struct	s_ast_node
{
	t_node_type			node_type;
	struct s_ast_node	*left;
	struct s_ast_node	*rigth;
	t_simple_cmd		*cmd;
}	t_ast;

int		ft_iswhitespace(char c);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstadd_front(t_token **lst, t_token *new);
void	ft_lstclear(t_token **lst);
void	ft_lstdelone(t_token *lst);
t_token	*ft_lstlast(t_token *lst);
t_token	*ft_lstnew(void *content, t_type type);
int		ft_lstsize(t_token *lst);
void	handle_sigquit(int sig);
void	handle_sigint(int sig);
void	token_error(t_token **token, char *message);
int		validation(t_token **token);

#endif
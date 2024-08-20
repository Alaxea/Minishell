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

// tokens (nodes) -> for tokenization input (first step lexing)
// "The shell breaks the input into tokens: words and operators" - Shell Command Language

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	char			*value;
	int				data_type;
}	t_token;

int		ft_iswhitespace(char c);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstadd_front(t_token **lst, t_token *new);
void	ft_lstclear(t_token **lst);
void	ft_lstdelone(t_token *lst);
t_token	*ft_lstlast(t_token *lst);
t_token	*ft_lstnew(void *content, t_type type);
int		ft_lstsize(t_token *lst);

#endif
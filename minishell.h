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
	NEWLINE,
	OPERATOR
}	t_type;

// tokens (nodes) -> for tokenization input (first step lexing)
// "The shell breaks the input into tokens: words and operators" - Shell Command Language

typedef struct s_token 
{
	t_token	*next;
	t_token	*prev;
	char	*value;
	int		data_type;
}	t_token;

int	ft_iswhitespace(char c);


#endif
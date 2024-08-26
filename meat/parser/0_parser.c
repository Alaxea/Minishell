/*
there are two major modes of parsing:
	1. ordinary token recognition
	2. heredoc proceeding (if heredoc token has been recognised)
*/

/*
	as input we receive a list of tokens -> sequences and operators
	now we will create structs list based on pipes
	[simple_cmd] -> [simple_cmd] -> [simple_cmd]
	one simple_cmd is finished when we encounter pipe
	
	plan:
		1. allocate simple_cmd struct
		2. if next token is an operator 
			a) check if it's pipe
				first simple_cmd is ready for final initialization, create next one
			b) if redirection
				place the information in the struct
*/

#include "../../minishell.h"

void	sc_initializer(t_simple_cmd *sc)
{
	sc->cmd = NULL;
	sc->heredoc = false;
	sc->input_path = NULL;
	sc->output_path = NULL;
	sc->output_path_append = NULL;
	sc->name = NULL;
	sc->parser_done = false;
	sc->path = NULL;
}

t_token	*ft_lstlast_sc(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_sc(t_token **lst, t_token *new)
{
	t_token	*tmp;
	if (new == NULL)
		return ;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
		new->prev = tmp;
	}
}

void	redir_modify(t_token *token, t_simple_cmd *simple_cmd, t_redir_type type)
{
	if (type == REDIR_INPUT)
		simple_cmd->input_path = token->next->value;
	if (type == REDIR_OUTPUT)
		simple_cmd->output_path = token->next->value;
	if (type == REDIR_APPEND)
		simple_cmd->output_path_append = token->next->value;
	if (type == REDIR_HEREDOC)
		simple_cmd->heredoc = true;
}

t_simple_cmd	*simple_cmd_creator(t_token *token)
{
	t_simple_cmd	*simple_cmd;
	t_token			*buf;

	buf = token;
	simple_cmd = malloc(sizeof(t_simple_cmd));
	if (!simple_cmd)
		return (0);
	sc_initializer(simple_cmd);
	while (buf && buf->data_type != PIPE)
	{
		if (buf->data_type != STANDARD)
		{
			redir_modify(buf, simple_cmd, buf->data_type);
			buf = buf->next;
		}
		else
		{
			simple_cmd->cmd = ft_split_quotes(buf->value, ' ');
			simple_cmd->name = simple_cmd->cmd[0];
		}
		buf = buf->next;
	}
	return (simple_cmd);
}
// int	parser(t_token *tokens)
// {
// 	t_token 		*buf;
// 	t_simple_cmd	*simple_cmd;
// 	t_simple_cmd	*sc_list;

// 	if (tokens == NULL)
//         return (-1);
// 	buf = tokens;
// 	while (buf)
// 	{
// 		if (buf->prev == NULL || buf->prev == PIPE)
// 		{
// 			simple_cmd = simple_cmd_creator(buf);
// 			ft_lstadd_back(&sc_list, simple_cmd);
// 		}
// 		buf = buf->next; // Move to the next token
// 	}
// 	return(0);
// }
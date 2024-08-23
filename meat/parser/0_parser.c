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


t_redir_type check_operator(char *str)
{
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (REDIR_HEREDOC);
		else
			return (REDIR_INPUT);
	}
	else if (str[0] == '>')
	{
		if (str[1] == '>')
			return (REDIR_APPEND);
		else
			return (REDIR_OUTPUT);
	}
	else
		return (PIPE);
}

redir_modify(t_token *token, t_simple_cmd *simple_cmd)
{
	t_redir_type type;

	type = check_operator(token->value);
	if (type == REDIR_INPUT)
		simple_cmd->input_path = token->next->value;
	if (type == REDIR_OUTPUT)
		simple_cmd->output_path = token->next->value;
	if (type == REDIR_APPEND)
		simple_cmd->output_path_append = token->next->value;
	if (type == REDIR_HEREDOC)
		simple_cmd->heredoc = true;
	if (type == PIPE)
		simple_cmd->parser_done = true;
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
	while (buf && !(simple_cmd->parser_done))
	{
		if (buf->data_type == OPERATOR)
		{
			redir_modify(buf, simple_cmd);
			buf = buf->next;
		}
		else if (buf->data_type == WORD)
		{
			simple_cmd->cmd = ft_split(buf->value, ' ');
			simple_cmd->cmd[0] = simple_cmd->name;
		}
		buf = buf->next;
	}
	return (simple_cmd);
}
int	parser(t_token **tokens)
{
	t_token *buf;

	buf = *tokens;
	while (buf)
	{
		simple_cmd_creator(buf);
	}


}
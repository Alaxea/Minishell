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

#include "./../../minishell.h"

void	sc_initializer(t_simple_cmd *sc)
{
	sc->cmd = NULL;
	sc->delimiter_heredoc = NULL;
	sc->heredoc = false;
	sc->input_path = NULL;
	sc->output_path = NULL;
	sc->output_path_append = NULL;
	sc->name = NULL;
	sc->parser_done = false;
	sc->path = NULL;
}

t_simple_cmd	*ft_lstlast_sc(t_simple_cmd *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_sc(t_simple_cmd **lst, t_simple_cmd *new)
{
	t_simple_cmd	*tmp;
	if (new == NULL)
		return ;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = ft_lstlast_sc(*lst);
		tmp->next = new;
		new->prev = tmp;
	}
}

char	*trim_the_value(char *old)
{
	size_t	start;
	char	*new;
	int		len;

	start = 0;
	len = ft_strlen(old);
	while (old[start] && old[start] != ' ')
		start++;
	if (old[start] != ' ')
	{
		free(old);
		return (NULL);
	}
	// printf("to be trimmed: %s\n", old);
	new = ft_substr(old, start + 1, len - start);
	// printf("new trimmed: %s\n", new);
	free(old);
	return (new);
}

char	*cut_out_path(char *value)
{
	int		stop;
	char	*ret;
	int		i;

	stop = 0;
	i = 0;
	while (value[stop] && value[stop] != ' ')
		stop++;
	// printf("%d\n", stop);
	ret = (char *)malloc(sizeof(char) * (stop + 1));
	if (!ret)
		return (NULL);
	while (i < stop)
	{
		ret[i] = value[i];
		i++;
	}
	ret[i] = '\0';
	// printf("%s\n", ret);

	return (ret);
}

void	redir_modify(t_token *token, t_simple_cmd *simple_cmd, t_redir_type type)
{
	if (type == REDIR_INPUT)
		simple_cmd->input_path = cut_out_path(token->next->value);
	else if (type == REDIR_OUTPUT)
		simple_cmd->output_path = cut_out_path(token->next->value);
	else if (type == REDIR_APPEND)
		simple_cmd->output_path_append = cut_out_path(token->next->value);
	else if (type == REDIR_HEREDOC)
	{
		simple_cmd->delimiter_heredoc = cut_out_path(token->next->value);
		simple_cmd->heredoc = true;
	}
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
			buf->next->value = trim_the_value(buf->next->value);
			if (!buf->next->value)
				buf = buf->next;
		}
		else
		{
			simple_cmd->cmd = ft_split_quotes(buf->value, ' ');
			if (!simple_cmd->cmd)
				return (NULL);
			simple_cmd->name = simple_cmd->cmd[0];
		}
		buf = buf->next;
	}
	return (simple_cmd);
}
t_simple_cmd	*parser(t_token *tokens)
{
	t_token 		*buf;
	t_simple_cmd	*simple_cmd;
	t_simple_cmd	*sc_list = NULL;

	if (tokens == NULL)
        return (NULL);
	buf = tokens;
	while (buf)
	{
		if (buf->prev == NULL || buf->prev->data_type == PIPE)
		{
			simple_cmd = simple_cmd_creator(buf);
			ft_lstadd_back_sc(&sc_list, simple_cmd);
		}
		buf = buf->next; // Move to the next token
	}
	return(sc_list);
}

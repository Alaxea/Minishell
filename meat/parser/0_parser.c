/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:51:43 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/11/22 10:36:29 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	sc->next = NULL;
	sc->prev = NULL;
	sc->fd_in = -1;
	sc->fd_out = -1;
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
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
		tmp = ft_lstlast_sc(*lst);
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
}

t_simple_cmd	*simple_cmd_creator(t_token *token)
{
	t_simple_cmd	*simple_cmd;
	t_token			*buf;

	buf = token;
	simple_cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
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
	t_token			*buf;
	t_simple_cmd	*simple_cmd;
	t_simple_cmd	*sc_list;

	sc_list = NULL;
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
		buf = buf->next;
	}
	return (sc_list);
}

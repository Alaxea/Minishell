/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:56:14 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/25 20:13:39 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	token_error(t_token **token, char *message)
{
	ft_lstclear(token);
	printf("%s\n", message);
}

int	operator_syntax(t_token *token)
{
	if (token->data_type != STANDARD && token->next == NULL)
	{
		printf("1\n");
		return (0);
	}
	if (token->data_type != STANDARD && token->data_type != PIPE && token->next->data_type != STANDARD)
	{
		printf("1\n");
		return (0);
	}
	if (token->data_type == REDIR_APPEND && token->next->data_type == REDIR_APPEND)
	{
		printf("append\n");
		return (0);
	}	
	if (token->data_type == REDIR_HEREDOC && token->next->data_type == REDIR_HEREDOC)
	{
		printf("heredoc\n");
		return (0);
	}
	if (token->data_type == REDIR_INPUT && token->next->data_type == REDIR_INPUT)
	{
		printf("input\n");
		return (0);
	}
	if (token->data_type == REDIR_OUTPUT && token->next->data_type == REDIR_OUTPUT)
	{
		printf("output\n");
		return (0);
	}
	if (token->data_type == PIPE && token->prev == NULL)
	{
		printf("2\n");
		return (0);
	}
	if (token->data_type == PIPE && token->next->data_type == PIPE)
	{
		printf("3\n");
		return (0);
	}
	return (1);
}
int	validation(t_token **token)
{
	t_token	*buffer;

	buffer = *token;
	while (buffer)
	{
		if (!operator_syntax(buffer))
		{
			token_error(token, "error - syntax error");
			return (0);
		}
		buffer = buffer->next;
	}
	return (1);
}

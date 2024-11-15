/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:37:16 by ugerkens          #+#    #+#             */
/*   Updated: 2024/08/25 22:07:28 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*ft_lstnew(void *content, t_redir_type type)
{
	t_token	*head;
	char	*str;

	str = (char *)content;
	head = malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	if (str[0] == '<' && str[1] == '<')
		type = REDIR_HEREDOC;
	if (str[0] == '>' && str[1] == '>')
		type = REDIR_APPEND;
	head->value = str;
	head->next = NULL;
	head->prev = NULL;
	head->data_type = type;
	return (head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:56:14 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/22 13:18:02 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	token_error(t_token **token, char *message)
{
	ft_lstclear(token);
	printf("%s\n", message);
}
// int	validation(t_token **token)
// {
// 	t_token	*buffer;

// 	buffer = *token;
// 	if (buffer->value[0] == '|')
// 	{
// 		token_error(token, "error - unexpected token '|'");
// 		return (0);
// 	}
// 	while (buffer)
// 	{
// 		if (buffer->data_type == OPERATOR && buffer->next->data_type == OPERATOR)
// 		{
// 			token_error(token, "error - two or more consecutive operators");
// 			return (0);
// 		}
// 		buffer = buffer->next;
// 	}
// 	return (1);
// }

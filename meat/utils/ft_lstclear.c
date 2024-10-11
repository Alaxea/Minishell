/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:09:59 by ugerkens          #+#    #+#             */
/*   Updated: 2024/08/21 13:40:53 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstclear(t_token **lst)
{
	t_token	*buffer;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		buffer = (*lst)->next;
		ft_lstdelone(*lst);
		*lst = buffer;
	}
	*lst = NULL;
}

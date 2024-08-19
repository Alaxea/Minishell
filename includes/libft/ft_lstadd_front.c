/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:38 by ugerkens          #+#    #+#             */
/*   Updated: 2024/08/19 13:56:32 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	ft_lstadd_front(t_token **lst, t_token *new)
{
	new->next = *lst;
	if (*lst != NULL)
		(*lst)->prev = new;
	*lst = new;
}

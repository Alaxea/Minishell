/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:47:39 by ugerkens          #+#    #+#             */
/*   Updated: 2024/08/20 15:39:36 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

// t_token	*ft_lstmap(t_token *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_token	*new_lst;
// 	t_token	*node;
// 	void	*mapped_content;

// 	if (!lst || !f || !del)
// 		return (NULL);
// 	new_lst = NULL;
// 	while (lst)
// 	{
// 		mapped_content = f(lst->value);
// 		node = ft_lstnew(mapped_content);
// 		if (!node)
// 		{
// 			del(mapped_content);
// 			ft_lstclear(&new_lst, del);
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&new_lst, node);
// 		lst = lst->next;
// 	}
// 	return (new_lst);
// }

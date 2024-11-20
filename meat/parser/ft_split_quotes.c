/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:21:00 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/11/20 14:45:19 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_countword(char *str, char c)
{
	int				i;
	int				count;
	t_quote_mode	mode;

	count = 0;
	mode = DEFAULT;
	i = 0;
	while (str[i] != '\0')
	{
		check_quote(&mode, str[i]);
		while (str[i] != '\0' && (str[i] == c && mode == DEFAULT))
			i++;
		if (str[i] != '\0' && mode == DEFAULT)
			count++;
		while (str[i] != '\0' && !(str[i] == c && mode == DEFAULT))
		{
			check_quote(&mode, str[i]);
			i++;
		}
	}
	return (count);
}

char	**ft_check_str(char *str, char c, t_quote_mode *mode)
{
	char	**strings;

	*mode = DEFAULT;
	if (str == NULL)
		return (NULL);
	strings = (char **)malloc(sizeof(char *) * (ft_countword(str, c) + 1));
	if (strings == NULL)
		return (NULL);
	return (strings);
}

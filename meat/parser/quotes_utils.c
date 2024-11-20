/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:22:55 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/11/20 15:04:54 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	*freestring(char **string, int i)
{
	int	a;

	a = 0;
	while (a < i)
		free(string[a++]);
	free(string);
	return (NULL);
}

static int	ft_wordlen(char *str, char c)
{
	int				i;
	t_quote_mode	mode;

	i = 0;
	mode = DEFAULT;
	while (str[i] != '\0')
	{
		check_quote(&mode, str[i]);
		if (mode == DEFAULT && str[i] == c)
			break ;
		i++;
	}
	return (i);
}

static char	*ft_word(char *str, char c)
{
	int		len_word;
	int		i;
	char	*word;

	len_word = ft_wordlen(str, c);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_quotes(char *str, char c)
{
	char			**strings;
	int				i;
	t_quote_mode	mode;

	mode = DEFAULT;
	strings = ft_check_str(str, c, &mode);
	if (strings == NULL || !str)
		return (NULL);
	i = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && (*str == c && mode == DEFAULT))
			str++;
		if (*str != '\0')
			strings[i++] = ft_word(str, c);
		if (i > 0 && strings[i - 1] == NULL)
			return (freestring(strings, i - 1));
		while (*str && !(*str == c && mode == DEFAULT))
		{
			check_quote(&mode, *str);
			str++;
		}
	}
	strings[i] = 0;
	return (strings);
}

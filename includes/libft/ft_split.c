/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:49:31 by astefans          #+#    #+#             */
/*   Updated: 2024/03/13 14:52:38 by astefans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	safe_malloc(char **words_v, int position, size_t buffer)
{
	int	i;

	i = 0;
	words_v[position] = malloc(buffer);
	if (NULL == words_v[position])
	{
		while (i < position)
			free(words_v[i++]);
		free(words_v);
		return (1);
	}
	return (0);
}

int	fill(char **words_v, char const *s, char delimeter)
{
	size_t		len;
	int			i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == delimeter && *s)
			++s;
		while (*s != delimeter && *s)
		{
			++len;
			++s;
		}
		if (len)
		{
			if (safe_malloc(words_v, i, len + 1))
				return (1);
			ft_strlcpy(words_v[i], s - len, len + 1);
		}
		i++;
	}
	return (0);
}

size_t	count_words(char const *s, char delimeter)
{
	size_t	words;
	int		inside_words;

	words = 0;
	while (*s)
	{
		inside_words = 0;
		while (*s == delimeter && *s)
			++s;
		while (*s != delimeter && *s)
		{
			if (!inside_words)
			{
				++words;
				inside_words = 42;
			}
			++s;
		}
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**words_v;

	if (NULL == s)
		return (NULL);
	words = 0;
	words = count_words(s, c);
	words_v = malloc((words + 1) * sizeof(char *));
	if (NULL == words_v)
		return (NULL);
	words_v[words] = NULL;
	if (fill(words_v, s, c))
		return (NULL);
	return (words_v);
}

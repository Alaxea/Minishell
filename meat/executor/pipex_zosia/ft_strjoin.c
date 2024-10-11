/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:23:57 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/07/26 14:11:54 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*string;
	int		length;

	if (s1 == NULL)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	string = (char *)malloc((sizeof(char) * (length + 1)));
	if (!string)
		return (NULL);
	while (s1[i] != '\0')
		string[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		string[j++] = s2[i++];
	string[j] = '\0';
	return (string);
}

// int main()
// { 
//     char *s1 = "z";
//     char *s2 = "z";
//     char *string;
//     string = ft_strjoin(s1, s2);
//     printf("%s\n", string);
//     free(string);
//     return 0;
// }

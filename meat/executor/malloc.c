/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:02:17 by astefans          #+#    #+#             */
/*   Updated: 2024/10/16 23:58:58 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void free_arguments(char **arguments) 
{
    int i;

	i = 0;
    if (arguments)
    {
        while (arguments[i]) 
	    {
            free(arguments[i]);
            i++;
        }
        free(arguments);
    }
}

//funkcja do kopiowania zmiennych środowiskowych
char    **ft_dup_envp(char **envp)
{
    char    **new_envp;
    int     i;
    int     count;

    count = 0;
    while (envp[count])
        count++;
    new_envp = (char **)malloc((count + 1) * sizeof(char *));
    if (!new_envp)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        new_envp[i] = ft_strdup(envp[i]);
        if (!new_envp[i])
        {
            while (--i >= 0)
                free(new_envp[i]);
            free(new_envp);
            return (NULL);
        }
        i++;
    }
    new_envp[i] = NULL;
    return (new_envp);
}


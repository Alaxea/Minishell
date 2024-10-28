/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:09:57 by astefans          #+#    #+#             */
/*   Updated: 2024/10/16 23:59:08 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*frees a pointer and sets NULL*/
void	free_pointer(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	clear_tab(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	clear_env(t_data *env)
{
	clear_tab(env->env_var);
}

void	exit_shell(t_data *env, char *mess, int fail)
{
	clear_env(env);
	if (fail == -1)
	{
		printf("Error: %s\n", mess);
		exit(EXIT_FAILURE);
	}
	else if (!fail)
		exit(EXIT_SUCCESS);
	else
	{
		printf("Error: %s\n", mess);
		exit(fail);
	}
}

/*void    ft_free_envp(char **envp)
{
    int i;

	i = 0;
    while (envp[i])
    {
        free(envp[i]);
        i++;
    }
    free(envp);
}*/

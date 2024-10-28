/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:09:57 by astefans          #+#    #+#             */
/*   Updated: 2024/10/28 20:14:31 by alicja           ###   ########.fr       */
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

int	ft_add_var(t_data *data, char *var, int overwrite) {
    char	*name;
    char	*value;
    int		i = 0;
    int		name_len;

    // Znajdź pozycję znaku '=' w `var`
    char *equals_pos = strchr(var, '=');
    if (!equals_pos)
        return (EXIT_FAILURE);

    // Wydziel nazwę zmiennej
    name_len = equals_pos - var;
    name = strndup(var, name_len);
    if (!name)
        return (EXIT_FAILURE);

    // Znajdź wartość zmiennej
    value = equals_pos + 1;

    // Przeszukaj istniejące zmienne, aby sprawdzić, czy istnieje już taka sama nazwa
    while (data->envp[i]) {
        if (strncmp(data->envp[i], name, name_len) == 0 && data->envp[i][name_len] == '=') {
            // Jeśli istnieje, nadpisz wartość, jeśli `overwrite` jest włączony
            if (overwrite) {
                free(data->envp[i]);
                data->envp[i] = malloc(strlen(name) + strlen(value) + 2);
                if (!data->envp[i]) {
                    free(name);
                    return (EXIT_FAILURE);
                }
                sprintf(data->envp[i], "%s=%s", name, value);
            }
            free(name);
            return (EXIT_SUCCESS);
        }
        i++;
    }

    // Zmień rozmiar `envp`, jeśli jest pełny
    if (i % ENV_INCREMENT == 0) {
        char **new_envp = realloc(data->envp, (i + ENV_INCREMENT + 1) * sizeof(char *));
        if (!new_envp) {
            free(name);
            return (EXIT_FAILURE);
        }
        data->envp = new_envp;
    }

    // Dodaj nową zmienną
    data->envp[i] = malloc(strlen(name) + strlen(value) + 2);
    if (!data->envp[i]) {
        free(name);
        return (EXIT_FAILURE);
    }
    sprintf(data->envp[i], "%s=%s", name, value);
    data->envp[i + 1] = NULL; // Dodaj NULL na końcu tablicy

    free(name);
    return (EXIT_SUCCESS);
}

// Zwalnianie całej tablicy `envp`
void	ft_free_env(char **env) {
    int i = 0;

    if (!env)
        return;
    while (env[i]) {
        free(env[i]);
        i++;
    }
    free(env);
}

void	ft_error(t_data *data, const char *msg, int exit_code) 
{
    if (msg)
        ft_putstr_fd((char *)msg, STDERR_FILENO);
    data->exit_code = exit_code;
}

char	*ft_strjoin_free(char *s1, const char *s2, int free_s1, int free_s2) {
    char	*result;
    size_t	len1 = s1 ? strlen(s1) : 0;
    size_t	len2 = s2 ? strlen(s2) : 0;

    result = malloc(len1 + len2 + 1); // +1 na znak końca '\0'
    if (!result)
        return NULL;

    if (s1)
        strcpy(result, s1); // Kopiujemy `s1` do `result`
    if (s2)
        strcpy(result + len1, s2); // Doklejamy `s2` do `result`

    if (free_s1 && s1)
        free(s1); // Zwalniamy `s1` jeśli `free_s1` jest ustawione
    if (free_s2 && s2)
        free((char *)s2); // Zwalniamy `s2` jeśli `free_s2` jest ustawione (rzutujemy na `char*`)

    return result;
}
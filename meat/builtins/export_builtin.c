/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicja <alicja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:17:08 by astefans          #+#    #+#             */
/*   Updated: 2024/10/28 20:06:07 by alicja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*int		export_builtin(t_data *env, t_simple_cmd *cmd)
{
	char	*temp; //do nazwy zmiennej
	char	*temp2; //do wartości zmiennej
	int		temp3;

	printf("Before checking args\n");
	if (!cmd->cmd[1])
	{
		ft_putstr_fd("export: Invalid arguments\n", 2);
		return (1);
	}
	printf("Before strchrn\n");
	temp3 = ft_strchrn(cmd->cmd[1], '=');
	printf("After strchrn: %d\n", temp3);
	if (temp3 == -1)
	{
		ft_putstr_fd("export: Invalid format\n", 2);
		return (1);
	}
	printf("Before extracting variable name\n");
	temp = ft_substr(cmd->cmd[1], 0, temp3);
	if (!temp)
    {
        ft_putstr_fd("Memory allocation error\n", 2);
        return (1);
    }
	printf("Variable name: %s\n", temp);
	if (set_env_var(env, temp) != NULL)
    {
        delete_env_var(env, temp);
    }
	printf("Before extracting variable value\n");
	temp2 = ft_substr(cmd->cmd[1], temp3 + 1,
			ft_strlen(cmd->cmd[1]) - temp3 - 1);
	if (!temp2)
    {
		free(temp);
        ft_putstr_fd("Memory allocation error\n", 2);
        return (1);
    }
	printf("Variable value: %s\n", temp2);
	add_env_var(env, temp, temp2);
	//free(temp);
	//free(temp2);
	printf("Export completed\n");
	return (0);
}*/

/*int export_builtin(t_data *env, t_simple_cmd *cmd) {
    char *temp;     // do nazwy zmiennej
    char *temp2;    // do wartości zmiennej
    int temp3;      // indeks znaku '='
    int i;          // indeks do iteracji
    int env_count;  // liczba zmiennych środowiskowych

    // Debugging output
    printf("Before checking args\n");

    if (!cmd->cmd[1]) {
        ft_putstr_fd("export: Invalid arguments\n", 2);
        return (1);
    }

    // Debugging output
    printf("Before strchrn\n");

    temp3 = ft_strchrn(cmd->cmd[1], '=');
    printf("After strchrn: %d\n", temp3);

    if (temp3 == -1) {
        ft_putstr_fd("export: Invalid format\n", 2);
        return (1);
    }

    // Debugging output
    printf("Before extracting variable name\n");

    temp = ft_substr(cmd->cmd[1], 0, temp3);
    if (!temp) {
        ft_putstr_fd("Memory allocation error\n", 2);
        return (1);
    }
    printf("Variable name: %s\n", temp);

    // Sprawdzenie, czy zmienna już istnieje
    env_count = 0;
    while (env->envp[env_count] != NULL)
        env_count++;

    for (i = 0; i < env_count; i++) {
        if (ft_strncmp(env->envp[i], temp, temp3) == 0 && env->envp[i][temp3] == '=') {
            // Zmienna istnieje, usuwamy ją
            free(env->envp[i]);
            break;
        }
    }

    // Debugging output
    printf("Before extracting variable value\n");

    temp2 = ft_substr(cmd->cmd[1], temp3 + 1, ft_strlen(cmd->cmd[1]) - temp3 - 1);
    if (!temp2) {
        free(temp);
        ft_putstr_fd("Memory allocation error\n", 2);
        return (1);
    }
    printf("Variable value: %s\n", temp2);

    // Przygotowanie nowej tablicy z jedną dodatkową pozycją
    char **new_env = malloc(sizeof(char *) * (env_count + 2)); // +2: jeden na nową zmienną i jeden na NULL
    if (!new_env) {
        free(temp);
        free(temp2);
        ft_putstr_fd("Memory allocation error\n", 2);
        return (1);
    }

    // Skopiowanie istniejących zmiennych do nowej tablicy
    for (i = 0; i < env_count; i++)
        new_env[i] = env->envp[i];

    // Ustawienie nowej zmiennej
    new_env[i] = malloc(strlen(temp) + strlen(temp2) + 2); // +2: na '=' i NULL
    if (!new_env[i]) {
        free(temp);
        free(temp2);
        free(new_env);
        ft_putstr_fd("Memory allocation error\n", 2);
        return (1);
    }

    // Ustawienie zmiennej w nowej tablicy
    strcpy(new_env[i], temp);
    strcat(new_env[i], "=");
    strcat(new_env[i], temp2);
    
    new_env[i + 1] = NULL; // Ustawienie ostatniego elementu na NULL

    // Uwolnienie starej tablicy i przypisanie nowej
    free(env->envp);
    env->envp = new_env;

    // Uwolnienie pamięci
    free(temp);
    free(temp2);

    printf("Export completed\n");
    return (0);
}*/

static void	ft_chose_exit_val(t_data *data, char *var) 
{
    int	i = 0;

    while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
        i++;
    if (var[i] == '\0' && !ft_strchr(var, '=')) {
        data->exit_code = 0; // Ustawienie exit_code na 0 w razie powodzenia
    } else if (var[i] != '\0' && !ft_strchr(var, '=')) {
        data->exit_code = 1; // Ustawienie exit_code na 1 w razie błędu
    }

    i = 0;
    while (var[i] && var[i] >= '0' && var[i] <= '9')
        i++;
    if (var[i] == '\0')
        data->exit_code = 1;
}

// Funkcja do wyświetlania zmiennych w formacie `declare -x`
static void	ft_print_parms(char **parms) {
    int i = 0;
    char **split;

    while (parms[i]) {
        split = ft_split(parms[i], '='); // Użyj funkcji ft_split
        if (!split)
            printf("ERROR: split failed\n");
        else
            printf("declare -x %s=\"%s\"\n", split[0], split[1] ? split[1] : "");
        ft_free_env(split);
        i++;
    }
}

// Funkcja obsługująca przypadek użycia błędnego polecenia export
static int	ft_usage(t_data *data) {
    data->exit_code = 0;
    ft_chose_exit_val(data, data->cmd->cmd[1]);
    return (EXIT_FAILURE);
}

// Funkcja obsługująca błąd podczas próby dodania zmiennej
static int	ft_export_error(t_data *data) {
    char *msg;

    if (data->cmd->cmd[1][ft_strlen(data->cmd->cmd[1]) - 1] == '=') {
        data->exit_code = 0;
        return (EXIT_FAILURE);
    }
    msg = ft_strjoin("Could not export variable: ", data->cmd->cmd[1]);
    if (!msg) return (EXIT_FAILURE);
    msg = ft_strjoin_free(msg, "\n", 1, 0); // Używamy funkcji łączącej i zwalniającej pamięć
    ft_error(data, msg, 0);
    free(msg);
    data->exit_code = 1;
    return (EXIT_FAILURE);
}

// Implementacja funkcji export_builtin
int	export_builtin(t_data *data, t_simple_cmd *cmd) {
    int i = 1;

    // Jeśli brak argumentów, wyświetl zmienne środowiskowe
    if (!cmd->cmd[1]) {
        ft_print_parms(data->envp);
        return (EXIT_SUCCESS);
    }

    // Iteracja przez podane argumenty export
    while (cmd->cmd[i]) {
        // Sprawdzenie, czy argument zawiera '='
        if (ft_strchr(cmd->cmd[i], '=') == NULL)
            return (ft_usage(data));
        // Próbujemy dodać zmienną środowiskową
        else if (ft_add_var(data, cmd->cmd[i], 0) == EXIT_FAILURE)
            return (ft_export_error(data));
        i++;
    }
    data->exit_code = 0; // Sukces
    return (EXIT_SUCCESS);
}
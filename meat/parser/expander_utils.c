#include "../../minishell.h"

char *find_env_var(char *str, int *start, int *stop)
{
	*start = 0;
	while (str[*start] != '$' && str[*start])
		(*start)++;
	(*start)++;
	*stop = *start;
	while (str[*stop] && str[*stop] != ' ' && str[*stop] != '"')
		(*stop)++;
	return (ft_substr(str, *start, *stop - *start));
}
char *trim_quotes(char *command)
{
	bool	trim;
	char	*copy;

	trim = false;
	copy = NULL;
	if (command[0] == '\'' && command[ft_strlen(command) - 1] == '\'')
		trim = true;
	else if (command[0] == '\"' && command[ft_strlen(command) - 1] == '\"')
		trim = true;
	if (trim)
	{
		copy = ft_substr(command, 1, ft_strlen(command) - 2);
		free(command);
		return (copy);
	}
	else
		return (command);
}

size_t	ft_len_until_eq_sign(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
	{
		i++;
	}
	return (i);
}

char	*get_env(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_len_until_eq_sign(env[i])) == 0)
			return (ft_strjoin("", (env[i] + ft_len_until_eq_sign(env[i]) + 1)));
		else
			i++;
	}
	return (ft_strdup(""));
}
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


#include "../../minishell.h"

char *trim_quotes(char *command)
{
	bool	trim;
	char	*copy;

	trim = false;
	copy = command;
	if (command[0] == '\'' || command[ft_strlen(command) - 1] == '\'')
		trim = true;
	else if (command[0] == '\"' || command[ft_strlen(command) - 1] == '\"')
		trim = true;
	if (trim)
	{
		copy = ft_substr(command, 1, ft_strlen(command) - 2);
		return (copy);
	}
	else
		return (command);

}


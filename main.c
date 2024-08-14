#include "minishell.h"

int main()
{
	char *input;

	while (1)
	{
		input = readline("minishell >> ");
		printf("%s\n", input);
	}

	return (0);

}
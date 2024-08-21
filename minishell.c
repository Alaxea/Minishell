#include "minishell.h"
/*command to compilation: cc -Wall -Wextra -Werror -o main main.c -lreadline
I tested it for exit and ls -l and it works*/
int	minishell()
{
	char *input;

	/*to initialize the history*/
	while(1)
	{
		input = readline("minishell>> ");
		if (!input)
		{
			printf("exit\n");
			exit(1);
		}
		/*if the line is empty, continue to the next iteration*/
		if (ft_strcmp(input, "") == 0)
		{
			free(input);
			continue;
		}
		/*to add line to the history*/
		add_history(input);
		/*if the user types "exit", break the loop and exit*/
		if (ft_strcmp(input, "exit") == 0) 
		{
            free(input);
            break;
        }
		/* and the WINNER for today is this: execute the command using the system's shell*/
		int status = system(input);
		/*to check if the command execution was successful*/
		if (status == -1) 
		{
            perror("system");
        }
		/*free the memory allocated by readline*/
		free(input);
	}
	return (0);
}

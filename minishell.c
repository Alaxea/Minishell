#include "minishell.h"
/*command to compilation: cc -Wall -Wextra -Werror -o main main.c -lreadline
I tested it for exit and ls -l and it works*/

int	parsing(t_data *data)
{
	data->tokens = token_creator(data->input);
	if (!data->tokens)
		return (0);
	if (!validation(&data->tokens))
		return (0);
	data->simple_cmds = parser(data->tokens);
	if (!data->simple_cmds)
		return (0);
	expand(&data->simple_cmds, data->envp);
	printf("after\n");
	return (1);
}
int	minishell(t_data *data)
{
	/*to initialize the history*/
	while(1)
	{
		data->input = readline("minishell>> ");
		if (!data->input)
		{
			printf("exit\n");
			exit(1);
		}
		/*if the line is empty, continue to the next iteration*/
		if (ft_strcmp(data->input, "") == 0)
		{
			free(data->input);
			continue;
		}
		/*to add line to the history*/
		add_history(data->input);
		/*if the user types "exit", break the loop and exit*/
		if (ft_strcmp(data->input, "exit") == 0) 
		{
            free(data->input);
            break;
        }
		parsing(data);
		/* and the WINNER for today is this: execute the command using the system's shell*/
		// int status = system(data->input);
		/*to check if the command execution was successful*/
		// if (status == -1) 
		// {
            // perror("system");
        // }
		/*free the memory allocated by readline*/
		free(data->input);
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	(void)argc;
	data.envp = envp;
	minishell(&data);
}

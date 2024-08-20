#include "../minishell.h"

/*
lexer is breaking input into tokens (words and operators), tokens will be a linked list because this form
allows us to dynamically add next tokens

During token recognition no substitutions shall be actually performed, 
and the result token shall contain exactly the characters that appear in the input 
*/

// static int	recognise_operator(char c)
// {
// 	if (c == '>')
// 		return (1);
// 	else if (c == '<')
// 		return ś(1);
// 	else if (c == '|')
// 		return (1);
// 	else (0);

// }

// word_or_operator()
// {
// 	if (recognise_operator())
// 		add_token();
// 	else
// 		add_token();

// }ś

int	ft_iswhitespace(char c)
{
	if (c == 9 || c == 32 || c == '\n')
		return (1);
	return (0);
}

void	check_quote(t_quote_mode *mode, char c)
{
	if (*mode == DEFAULT)
	{
		if (c == '\'')
			*mode = SINGLE_Q;
		else if (c == '\"')
			*mode = DOUBLE_Q;
	}
	else if (*mode == SINGLE_Q && c == '\'')
		*mode = DEFAULT;
	else if (*mode == DOUBLE_Q && c == '\"')
		*mode == DEFAULT;
}

token_creator(char *input)
{
	int				i;
	t_quote_mode	mode;
	t_token 		token;

	mode = DEFAULT;
	while (input[i])
	{
		check_quote(&mode, input[i]);
		if (ft_iswhitespace(input[i]) && mode == DEFAULT)
			word_or_operator();
		/*
		quote(mode);
		if (input[i] == whitespace (tab or space) and mode != quoted)
			delimit token
				----- word_or_operator();
		NOT NEEDED \/
		if mode == quoted && input[i] = quote
			delimit token
			---- word();
		*/
	}


}
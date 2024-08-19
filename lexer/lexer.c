#include "../minishell.h"

/*
lexer is breaking input into tokens (words and operators), tokens will be a linked list because this form
allows us to dynamically add next tokens

During token recognition no substitutions shall be actually performed, 
and the result token shall contain exactly the characters that appear in the input 
*/

token_creator(char *input)
{
	int		i;
	quote_mode	mode;
	t_token token;

	mode = DEFAULT;
	while (input[i])
	{
		/*
		if (quote())
			mode == quoted
		if (input[i] == whitespace (tab or space) and mode != quoted)
			delimit token
				----- word_or_operator();
		if mode == quoted && input[i] = quote
			delimit token
			---- word();
		*/
	}


}
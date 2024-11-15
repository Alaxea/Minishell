/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:36:08 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/23 22:45:19 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
lexer is breaking input into tokens (words and operators), tokens will be a linked list because this form
allows us to dynamically add next tokens

During token recognition no substitutions shall be actually performed, 
and the result token shall contain exactly the characters that appear in the input 
*/
static int	recognise_operator(char c);

t_token *add_token(char *input, int max, int start, t_type type)
{
	char	*str;
	int		i;

	while (ft_iswhitespace(input[max - 1]))
		max--;
	while (ft_iswhitespace(input[start]))
		start++;
	if ((max - start) == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (max - start) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < max)
	{
		str[i] = input[start];
		i++;
		start++;
	}
	str[i] = '\0';
	if (recognise_operator(input[start]))
		type = OPERATOR;
	else
		type = WORD;
	return (ft_lstnew(str, type));
}

static int	recognise_operator(char c)
{
	if (c == '>')
		return (1);
	else if (c == '<')
		return (1);
	else if (c == '|')
		return (1);
	else
		return (0);

}

void	word_or_operator(char *input, int max, int start, t_token **token)
{
	t_token *word;
	t_token	*operator;

	word = add_token(input, max, start, WORD);
	if (word)
		ft_lstadd_back(token, word);
	start = max;
	while (recognise_operator(input[max]) && input[max] == input[start])
		max++;
	operator = add_token(input, max, start, OPERATOR);
		if (operator)
	ft_lstadd_back(token, operator);
}

int	ft_iswhitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
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
		*mode = DEFAULT;
}

int	token_creator(char *input)
{
	int				i;
	int				start;
	t_quote_mode	mode;
	t_token 		*token;

	i = 0;
	start = 0;
	mode = DEFAULT;
	token = NULL;
	while (input[i])
	{
		check_quote(&mode, input[i]);
		if (recognise_operator(input[i + 1]) && mode == DEFAULT)
		{
			word_or_operator(input, i + 1, start, &token);
			if (recognise_operator(input[i + 2]) && input[i + 2] == input[i + 1])
				i += 1;
			start = i + 2;
		}
		if (input[i + 1] == '\0')
			ft_lstadd_back(&token, add_token(input, i + 1, start, WORD));
		i++;
	}
	t_token *buf = token;
	while (buf)
	{
		printf("value: %s\n", buf->value); 
		buf = buf->next;
	}
	// else
	// 	return (validation(&token));
	return (1);
}

int main()
{
	while (1)
	{
		char *input = readline("minishell: ");
		token_creator(input);
	}

	return (0);
}
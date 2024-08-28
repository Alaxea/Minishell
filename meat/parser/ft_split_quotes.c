#include "../../minishell.h"


static int	ft_countword(char *str, char c)
{
	int				i;
	int				count;
	t_quote_mode	mode = DEFAULT;	// Initialize mode

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		check_quote(&mode, str[i]);
		while (str[i] != '\0' && (str[i] == c && mode == DEFAULT))
			i++;
		if (str[i] != '\0' && mode == DEFAULT)
			count++;
		while (str[i] != '\0' && !(str[i] == c && mode == DEFAULT))
		{
			check_quote(&mode, str[i]);
			i++;
		}
	}
	return (count);
}

static int	ft_wordlen(char *str, char c)
{
	int	i;
	t_quote_mode mode = DEFAULT;	// Initialize mode

	i = 0;
	while (str[i] != '\0')
	{
		check_quote(&mode, str[i]);
		if (mode == DEFAULT && str[i] == c)
			break ;
		i++;
	}
	return (i);
}

static char	*ft_word(char *str, char c)
{
	int		len_word;
	int		i;
	char	*word;

	len_word = ft_wordlen(str, c);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_check_str(char *str, char c, t_quote_mode *mode)
{
	char **strings;

	*mode = DEFAULT;
	if (str == NULL)
		return (NULL);
	strings = (char **)malloc(sizeof(char *) * (ft_countword(str, c) + 1));
	if (strings == NULL)
		return (NULL);
	return (strings);
}

static void	*freestring(char **string, int i)
{
	int	a;

	a = 0;
	while (a < i)
		free(string[a++]);
	free(string);
	return (NULL);
}

char	**ft_split_quotes(char *str, char c)
{
	char		**strings;
	int			i;
	t_quote_mode	mode;  // Initialize mode

	strings = ft_check_str(str, c, &mode);
	if (strings == NULL || !str)
		return (NULL);
	i = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && (*str == c && mode == DEFAULT))
			str++;
		if (*str != '\0')
			strings[i++] = ft_word(str, c);
		if (i > 0 && strings[i - 1] == NULL)
			return (freestring(strings, i - 1));
		while (*str && !(*str == c && mode == DEFAULT))
		{
			check_quote(&mode, *str);
			str++;
		}
	}
	strings[i] = 0;
	return (strings);
}

// int main()
// {
// 	char **array = ft_split_quotes("my command is \"    letsss   goooo \"    ", ' ');
// 	int i = 0;
// 	while (array[i] != NULL)
// 	{
// 		printf("%s\n", array[i]);
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// 	return (0);
// }

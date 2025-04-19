#include "minishell.h"

int	quote_checker(const char *input)
{
	int i = 0;
	int single_quote = 0;
	int double_quote = 0;

	while (input[i])
	{
		if (input[i] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (input[i] == '\"' && single_quote == 0)
			double_quote = !double_quote;
		i++;
	}
	if (single_quote || double_quote)
	{
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		return (0);
	}
	return (1);
}

char *quote_trimmer(const char *input)
{
	char	*result;
	size_t	i = 0;
	int		in_double_quote = 0;

	if (!input)
		return (NULL);
	result = calloc(1, 1);
	if (!result)
		return (NULL);

	while (input[i])
	{
		if (input[i] == '"' && !in_double_quote)
		{
			in_double_quote = 1;
			i++;
		}
		else if (input[i] == '"' && in_double_quote)
		{
			in_double_quote = 0;
			i++;
		}
		else
		{
			result = strappend_char(result, input[i]);
			i++;
		}
	}
	return (result);
}

#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libft/libft.h"

int g_exit_status = 0;

static char	*get_env_value(const char *key)
{
	if (!key || !*key)
		return (NULL);
	return (getenv(key));
}

static char *expand_variable(const char *str, size_t *i)
{
	size_t start = ++(*i);
	char *var, *value;

	if (str[start] == '?') // $? için
	{
		(*i)++;
		return ft_itoa(g_exit_status);
	}
	if (!str[start] || !(ft_isalpha(str[start]) || str[start] == '_'))
		return strdup("$"); // sadece $ yazılmışsa veya geçersizse

	size_t len = 0;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++, len++;

	var = strndup(str + start, len);
	value = get_env_value(var);
	free(var);
	return value ? strdup(value) : strdup("");
}

char *expand_input(const char *input)
{
	char *result = calloc(1, 1);
	size_t i = 0;
	int in_single_quote = 0;
	int in_double_quote = 0;

	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			result = strappend_char(result, input[i++]);
		}
		else if (input[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			result = strappend_char(result, input[i++]);
		}
		else if (input[i] == '$')
		{
			if (in_single_quote)
				result = strappend_char(result, input[i++]); // Tek tırnak içindeyse $ olduğu gibi yazılır
			else
			{
				char *expanded = expand_variable(input, &i);
				result = strappend_str(result, expanded);
				free(expanded);
			}
		}
		else
			result = strappend_char(result, input[i++]);
	}
	return result;
}


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

	if (str[start] == '?')
	{
		(*i)++;
		return ft_itoa(g_exit_status, 10);
	}
	if (!str[start] || !(ft_isalpha(str[start]) || str[start] == '_'))
		return ft_strdup("$");

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
	char	*result;
	size_t	i;
	int		in_single_quote;
	int		in_double_quote;

	result = calloc(1, 1);
	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			result = strappend_char(result, input[i]);
			i++;
		}
		else if (input[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			result = strappend_char(result, input[i]);
			i++;
		}
		else if (input[i] == '$')
		{
			if (in_single_quote)
			{
				result = strappend_char(result, input[i]);
				i++;
			}
			else
			{
				char *expanded = expand_variable(input, &i);
				result = strappend_str(result, expanded);
				free(expanded);
			}
		}
		else
		{
			result = strappend_char(result, input[i]);
			i++;
		}
	}
	return (result);
}


void expand_token_list(t_token *tokens)
{
	t_token *tmp;
	char *expanded;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == T_WORD)
		{
			if (tmp->value[0] == '\'' && tmp->value[ft_strlen(tmp->value) - 1] == '\'')
			{
				tmp = tmp->next;
				continue;
			}
			expanded = expand_input(tmp->value);
			free(tmp->value);
			tmp->value = expanded;
		}
		tmp = tmp->next;
	}
}

#include "libft/libft.h"
#include "minishell.h"
#include <stdlib.h>

static char	*append_char(char *result, char c)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = '\0';
	return (ft_strjoin_free(result, temp, 1));
}

static char	*expand_variable(const char *str)
{
	char	*result;
	size_t	i;
	char	*env_value;

	if (!str || !ft_strchr(str, '$'))
		return (ft_strdup(str));
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			env_value = handle_variable(str, &i);
			if (env_value)
				result = ft_strjoin_free(result, env_value, 1);
		}
		else
			result = append_char(result, str[i++]);
	}
	return (result);
}

static void	handle_double_quotes(t_token *current)
{
	char	*trimmed;
	char	*expanded;

	trimmed = ft_strtrim(current->value, "\"");
	expanded = expand_variable(trimmed);
	free(trimmed);
	free(current->value);
	current->value = ft_strjoin("\"", expanded);
	current->value = ft_strjoin_free(current->value, "\"", 1);
	free(expanded);
}

static void	handle_word_token(t_token *current)
{
	char	*expanded;

	if (current->value[0] == '\'' && current->value[ft_strlen(current->value)
			- 1] == '\'')
		return ;
	if (current->value[0] == '"' && ft_strchr(current->value, '$'))
		handle_double_quotes(current);
	else
	{
		expanded = expand_variable(current->value);
		free(current->value);
		current->value = expanded;
	}
}

t_token	*expander(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->value && current->type == TOKEN_WORD)
			handle_word_token(current);
		current = current->next;
	}
	return (tokens);
}

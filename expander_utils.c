#include "minishell.h"

char	*get_env_value(const char *key)
{
	if (!key || !*key)
		return (NULL);
	return (getenv(key));
}

size_t	get_env_key_len(const char *str, size_t *i)
{
	size_t	len;

	len = 0;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		(*i)++;
		len++;
	}
	return (len);
}

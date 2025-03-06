#include <stdlib.h>
#include "libft/libft.h"

char	*ft_strndup(const char *s, int n)
{
	char	*dup;
	int		i;

	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strjoin_free(char *s1, const char *s2, int free_s1)
{
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	new_str = ft_strjoin(s1, s2);
	if (free_s1)
		free(s1);
	return (new_str);
}

char	*handle_variable(const char *str, size_t *i)
{
	char	*var_start;
	size_t	var_len;
	char	*var_name;
	char	*env_value;

	var_start = (char *)&str[*i + 1];
	var_len = 0;
	while (var_start[var_len] && (ft_isalnum(var_start[var_len])
			|| var_start[var_len] == '_'))
		var_len++;
	var_name = ft_strndup(var_start, var_len);
	env_value = getenv(var_name);
	free(var_name);
	*i += var_len + 1;
	return (env_value);
}

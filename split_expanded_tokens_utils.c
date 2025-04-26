#include "minishell.h"

void	ft_free_strarray(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

t_token	*create_token(const char *value, t_token_type type, int joined)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->type = type;
	new->joined = joined;
	new->next = NULL;
	return (new);
}

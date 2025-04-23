#include "minishell.h"

static void	ft_free_strarray(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static t_token	*create_token(const char *value, t_token_type type, int joined)
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

void	split_expanded_tokens(t_token **head)
{
	t_token	*cur;
	t_token	*prev;
	t_token	*new_tokens;
	t_token	*last;
	t_token	*t;
	char	**parts;
	int		i;

	cur = *head;
	prev = NULL;
	while (cur)
	{
		if (cur->type == T_WORD && ft_strchr(cur->value, ' '))
		{
			parts = ft_split(cur->value, ' ');
			if (!parts)
				return ;
			new_tokens = NULL;
			last = NULL;
			i = 0;
			while (parts[i])
			{
				t = create_token(parts[i], T_WORD, 0);
				if (!new_tokens)
					new_tokens = t;
				else
					last->next = t;
				last = t;
				i++;
			}
			free(cur->value);
			free(cur);
			if (prev)
				prev->next = new_tokens;
			else
				*head = new_tokens;
			last->next = cur->next;
			cur = last->next;
			ft_free_strarray(parts);
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

#include "minishell.h"

void	merge_joined_tokens(t_token **tokens)
{
	t_token	*cur;
	t_token	*next;
	char	*merged;

	cur = *tokens;
	while (cur && cur->next)
	{
		next = cur->next;
		while (next && next->type == T_WORD && next->joined == 1)
		{
			merged = strappend_str(ft_strdup(cur->value), next->value);
			free(cur->value);
			cur->value = merged;
			cur->next = next->next;
			free(next->value);
			free(next);
			next = cur->next;
		}
		cur = cur->next;
	}
}

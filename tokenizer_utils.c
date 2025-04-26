#include "minishell.h"

t_token_type	get_operator_type(const char *s)
{
	if (s[0] == '>' && s[1] == '>')
		return (T_APPEND);
	else if (s[0] == '<' && s[1] == '<')
		return (T_HEREDOC);
	else if (s[0] == '>')
		return (T_REDOUT);
	else if (s[0] == '<')
		return (T_REDIN);
	else if (s[0] == '|')
		return (T_PIPE);
	return (T_WORD);
}

void	add_token(t_token **head, char *value, t_token_type type,
		int joined)
{
	t_token	*new;
	t_token	*cur;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = value;
	new->type = type;
	new->joined = joined;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

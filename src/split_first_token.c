#include "minishell.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;

	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static int	can_split_token(t_token *token)
{
	if (!token || token->next)
		return (0);
	if (token->type != T_WORD || token->trimmed)
		return (0);
	if (!ft_strchr(token->value, ' '))
		return (0);
	return (1);
}

static void apply_split(t_token *cur, char *first, char *rest)
{
	t_token	*second;

	if (first && rest)
	{
		free(cur->value);
		cur->value = first;
		second = create_token(rest, T_WORD, 0, 0);
		cur->next = second;
	}
	free(rest);
}

void	split_first_token_head_tail(t_token **tokens)
{
	t_token	*cur;
	char	*rest;
	char	*first;
	int		i;

	cur = *tokens;
	if (!can_split_token(cur))
		return ;
	i = 0;
	while (cur->value[i] == ' ')
		i++;
	while (cur->value[i] && cur->value[i] != ' ')
		i++;
	first = ft_substr(cur->value, 0, i);
	while (cur->value[i] == ' ')
		i++;
	rest = ft_strdup(&cur->value[i]);
	apply_split(cur, first, rest);
}


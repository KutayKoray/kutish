#include "minishell.h"

static int	is_operator_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

static int	operator_length(const char *s)
{
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		return (2);
	return (1);
}

static t_token_type	get_operator_type(const char *s)
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

static void	add_token(t_token **head, char *value, t_token_type type, int joined)
{
	t_token *new = malloc(sizeof(t_token));
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
		t_token *cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

static int	read_quoted(const char *str, int start, char quote)
{
	int i = start + 1;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

static int	read_plain(const char *str, int start)
{
	int i = start;
	while (str[i] && str[i] != '\'' && str[i] != '"' && str[i] != ' ' && !is_operator_char(str[i]))
		i++;
	return (i);
}

static void	tokenize_segment(t_token **head, const char *str, int start, int end, int joined)
{
	if (start < end)
		add_token(head, strndup(&str[start], end - start), T_WORD, joined);
}

t_token	*tokenize(const char *input)
{
	t_token	*list = NULL;
	int		i = 0;
	int		prev_was_space = 1;

	while (input[i])
	{
		if (input[i] == ' ')
		{
			prev_was_space = 1;
			i++;
		}
		else if (is_operator_char(input[i]))
		{
			int len = operator_length(&input[i]);
			add_token(&list, strndup(&input[i], len), get_operator_type(&input[i]), 0);
			i += len;
			prev_was_space = 1;
		}
		else
		{
			while (input[i] && input[i] != ' ' && !is_operator_char(input[i]))
			{
				int start = i;
				if (input[i] == '\'' || input[i] == '"')
					i = read_quoted(input, i, input[i]);
				else
					i = read_plain(input, i);
				tokenize_segment(&list, input, start, i, prev_was_space == 0);
				prev_was_space = 0;
			}
		}
	}
	return (list);
}

void	free_token_list(t_token *tokens)
{
	t_token *tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

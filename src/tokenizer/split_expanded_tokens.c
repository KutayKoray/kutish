/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:06 by kkoray            #+#    #+#             */
/*   Updated: 2025/06/12 19:12:27 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static t_token	*create_token(const char *value, t_token_type type, int joined, int trimmed)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->type = type;
	new->joined = joined;
	new->trimmed = trimmed;
	new->next = NULL;
	return (new);
}

static t_token	*create_token_list_from_split(char **parts, t_token *cur)
{
	t_token	*new_tokens;
	t_token	*last;
	t_token	*t;
	int		i;

	new_tokens = NULL;
	last = NULL;
	i = 0;
	while (parts[i])
	{
		t = create_token(parts[i], T_WORD, 0, cur->trimmed);
		if (!new_tokens)
			new_tokens = t;
		else
			last->next = t;
		last = t;
		i++;
	}
	return (new_tokens);
}

static void	replace_current_with_split(t_token **head, t_token *cur,
		t_token *prev, t_token *new_tokens)
{
	t_token	*last;

	last = new_tokens;
	while (last && last->next)
		last = last->next;
	if (prev)
		prev->next = new_tokens;
	else
		*head = new_tokens;
	last->next = cur->next;
	free(cur->value);
	free(cur);
}

static void	process_token_if_split_needed(t_token **head, t_token **cur,
		t_token **prev)
{
	t_token	*new_tokens;
	char	**parts;

	parts = ft_split((*cur)->value, ' ');
	if (!parts)
		return ;
	new_tokens = create_token_list_from_split(parts, *cur);
	replace_current_with_split(head, *cur, *prev, new_tokens);
	free_str_arr(parts);
	*cur = new_tokens;
}

static void	advance_cursor_after_split(t_token **cur)
{
	while (*cur && (*cur)->next)
		*cur = (*cur)->next;
	if (*cur)
		*cur = (*cur)->next;
}

void	split_expanded_tokens(t_token **head)
{
	t_token	*cur;
	t_token	*prev;

	cur = *head;
	prev = NULL;
	while (cur)
	{
		if (cur->type == T_WORD && ft_strchr(cur->value, ' ') && cur->expanded)
		{
			if (prev && prev->type == T_HEREDOC)
			{
				prev = cur;
				cur = cur->next;
				continue ;
			}
			process_token_if_split_needed(head, &cur, &prev);
			advance_cursor_after_split(&cur);
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

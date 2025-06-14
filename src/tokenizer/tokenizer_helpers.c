/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:08 by kkoray            #+#    #+#             */
/*   Updated: 2025/06/14 12:54:55 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int	operator_length(const char *s)
{
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		return (2);
	return (1);
}

int	skip_space(const char *input, int i, int *prev_was_space)
{
	if (input[i] == ' ' || input[i] == '\t')
	{
		*prev_was_space = 1;
		return (i + 1);
	}
	return (i);
}

int	is_operator_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	read_word(const char *str, int start)
{
	char	quote;
	size_t	i;

	i = start;
	while (str[i] && !is_operator_char(str[i])
		&& str[i] != ' ' && str[i] != '\t')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				i++;
		}
		else
			i++;
	}
	return (i);
}

t_token	*create_token(const char *value, t_token_type type,
	int joined, int trimmed)
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

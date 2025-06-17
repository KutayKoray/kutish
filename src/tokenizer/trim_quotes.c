/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:20:14 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/17 20:20:16 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static void	skip_and_copy_quoted(const char *value, int *i,
	char *cleaned, int *j)
{
	char	quote;

	quote = value[(*i)++];
	while (value[*i] && value[*i] != quote)
		cleaned[(*j)++] = value[(*i)++];
	if (value[*i] == quote)
		(*i)++;
}

static char	*remove_mixed_quotes(const char *value)
{
	char	*cleaned;
	int		i;
	int		j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(value);
	cleaned = malloc(len + 1);
	if (!cleaned)
		return (NULL);
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '"')
			skip_and_copy_quoted(value, &i, cleaned, &j);
		else
			cleaned[j++] = value[i++];
	}
	cleaned[j] = '\0';
	return (cleaned);
}

static void	process_token_quotes(t_token *token)
{
	char	*cleaned;

	cleaned = remove_mixed_quotes(token->value);
	if (!cleaned)
		return ;
	free(token->value);
	token->value = cleaned;
}

void	trim_token_quotes(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == T_WORD)
			process_token_quotes(tmp);
		tmp = tmp->next;
	}
}

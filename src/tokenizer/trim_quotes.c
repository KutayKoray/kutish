/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:35:51 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/14 13:01:40 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static char	*remove_inner_matching_quotes(const char *str, char quote)
{
	char	*result;
	int		i;
	int		j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != quote)
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

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
	char	*trimmed;
	char	*cleaned;
	size_t	len;
	char	quote;

	len = ft_strlen(token->value);
	if (len >= 2
		&& ((token->value[0] == '"' && token->value[len - 1] == '"')
			|| (token->value[0] == '\'' && token->value[len - 1] == '\'')))
	{
		quote = token->value[0];
		token->trimmed = 1;
		trimmed = ft_substr(token->value, 1, len - 2);
		if (!trimmed)
			return ;
		cleaned = remove_inner_matching_quotes(trimmed, quote);
		free(trimmed);
	}
	else
		cleaned = remove_mixed_quotes(token->value);
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

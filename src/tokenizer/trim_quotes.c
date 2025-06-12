/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:35:51 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/12 19:17:55 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static char	*remove_inner_matching_quotes(const char *str, char quote)
{
	int		i = 0;
	int		j = 0;
	size_t	len = ft_strlen(str);
	char	*result = malloc(len + 1);

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

static char	*remove_mixed_quotes(const char *value)
{
	int		i;
	int		j;
	char	quote;
	char	*cleaned;
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
		{
			quote = value[i++];
			while (value[i] && value[i] != quote)
				cleaned[j++] = value[i++];
			if (value[i] == quote)
				i++;
		}
		else
			cleaned[j++] = value[i++];
	}
	cleaned[j] = '\0';
	return (cleaned);
}

void	trim_token_quotes(t_token *tokens)
{
	t_token	*tmp;
	char	*trimmed;
	char	*cleaned;
	size_t	len;
	char	quote;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == T_WORD)
		{
			len = ft_strlen(tmp->value);
			if (len >= 2 && ((tmp->value[0] == '"' && tmp->value[len - 1] == '"')
				|| (tmp->value[0] == '\'' && tmp->value[len - 1] == '\'')))
			{
				quote = tmp->value[0];
				tmp->trimmed = 1;
				trimmed = ft_substr(tmp->value, 1, len - 2);
				if (!trimmed)
				{
					tmp = tmp->next;
					continue;
				}
				cleaned = remove_inner_matching_quotes(trimmed, quote);
				free(trimmed);
			}
			else
				cleaned = remove_mixed_quotes(tmp->value);
			free(tmp->value);
			tmp->value = cleaned;
		}
		tmp = tmp->next;
	}
}

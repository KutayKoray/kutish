/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:29 by kkoray            #+#    #+#             */
/*   Updated: 2025/06/16 15:13:28 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

char	*expand_variable(t_expand_ctx *ctx, const char *str, size_t *i)
{
	size_t	start;
	size_t	len;
	char	*var;
	char	*value;

	start = ++(*i);
	if (str[start] == '?')
	{
		(*i)++;
		return (ft_itoa(*exit_status()));
	}
	if (!str[start] || !(ft_isalpha(str[start]) || str[start] == '_'))
		return (ft_strdup("$"));
	len = get_env_key_len(str, i);
	var = ft_strndup(str + start, len);
	value = get_env_value(ctx->env, var);
	free(var);
	if (value)
	{
		ctx->expanded = 1;
		return (ft_strdup(value));
	}
	else
		return (ft_strdup(""));
}

size_t	get_env_key_len(const char *str, size_t *i)
{
	size_t	len;

	len = 0;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		(*i)++;
		len++;
	}
	return (len);
}

char	*char_to_str(char c)
{
	char	*str;

	str = malloc(2 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void	remove_token_node(t_token **head, t_token *prev, t_token *cur)
{
	if (prev)
		prev->next = cur->next;
	else
		*head = cur->next;
	free(cur->value);
	free(cur);
}

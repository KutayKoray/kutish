/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:32 by kkoray            #+#    #+#             */
/*   Updated: 2025/04/26 12:32:33 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int			g_exit_status = 0;

static char	*expand_variable(const char *str, size_t *i)
{
	size_t	start;
	size_t	len;
	char	*var;
	char	*value;

	start = ++(*i);
	if (str[start] == '?')
	{
		(*i)++;
		return (ft_itoa(g_exit_status, 10));
	}
	if (!str[start] || !(ft_isalpha(str[start]) || str[start] == '_'))
		return (ft_strdup("$"));
	len = get_env_key_len(str, i);
	var = ft_strndup(str + start, len);
	value = get_env_value(var);
	free(var);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}

static void	handle_quotes(const char *input, size_t *i, t_expand_ctx *ctx)
{
	if (input[*i] == '\'' && !ctx->in_double_quote)
	{
		ctx->in_single_quote = !ctx->in_single_quote;
		ctx->result = strappend_char(ctx->result, input[(*i)++]);
	}
	else if (input[*i] == '"' && !ctx->in_single_quote)
	{
		ctx->in_double_quote = !ctx->in_double_quote;
		ctx->result = strappend_char(ctx->result, input[(*i)++]);
	}
}

static void	handle_dollar(const char *input, size_t *i, t_expand_ctx *ctx)
{
	char	*expanded;

	if (ctx->in_single_quote)
		ctx->result = strappend_char(ctx->result, input[(*i)++]);
	else
	{
		expanded = expand_variable(input, i);
		ctx->result = strappend_str(ctx->result, expanded);
		free(expanded);
	}
}

char	*expand_input(const char *input)
{
	t_expand_ctx	ctx;
	size_t			i;

	ctx.result = calloc(1, 1);
	ctx.in_single_quote = 0;
	ctx.in_double_quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			handle_quotes(input, &i, &ctx);
		else if (input[i] == '$')
			handle_dollar(input, &i, &ctx);
		else
			ctx.result = strappend_char(ctx.result, input[i++]);
	}
	return (ctx.result);
}

void	expand_token_list(t_token *tokens)
{
	t_token	*tmp;
	char	*expanded;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == T_WORD)
		{
			if (tmp->value[0] == '\'' && tmp->value[ft_strlen(tmp->value)
					- 1] == '\'')
			{
				tmp = tmp->next;
				continue ;
			}
			expanded = expand_input(tmp->value);
			free(tmp->value);
			tmp->value = expanded;
		}
		tmp = tmp->next;
	}
}

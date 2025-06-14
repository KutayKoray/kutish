/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:32 by kkoray            #+#    #+#             */
/*   Updated: 2025/06/14 12:15:36 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static void	append_char_to_result(const char *input, size_t *i,
	t_expand_ctx *ctx)
{
	char	*tmp;
	char	*char_str;

	char_str = char_to_str(input[*i]);
	tmp = ft_strjoin(ctx->result, char_str);
	free(char_str);
	free(ctx->result);
	ctx->result = tmp;
	(*i)++;
}

void	process_char(const char *input, size_t *i, t_expand_ctx *ctx,
	t_token *token)
{
	if (input[*i] == '\'')
		handle_quotes(input, i, ctx);
	else if (input[*i] == '"')
	{
		ctx->first_quote = input[*i];
		handle_quotes(input, i, ctx);
	}
	else if (input[*i] == '$')
	{
		handle_dollar(input, i, ctx);
		if (token && ctx->expanded)
			token->expanded = 1;
	}
	else if (input[*i] == '~')
		handle_tilde(input, i, ctx);
	else
		append_char_to_result(input, i, ctx);
}

char	*expand_input(const char *input, t_token *token, t_env *env)
{
	t_expand_ctx	ctx;
	size_t			i;

	ctx.result = ft_calloc(1, 1);
	ctx.expanded = 0;
	ctx.in_single_quote = 0;
	ctx.in_double_quote = 0;
	ctx.first_quote = 0;
	ctx.env = env;
	i = 0;
	while (input[i])
		process_char(input, &i, &ctx, token);
	return (ctx.result);
}

void	expand_token_list(t_token *tokens, t_env *env)
{
	t_token	*cur;
	t_token	*prev;
	char	*expanded;

	cur = tokens;
	prev = NULL;
	while (cur)
	{
		if (cur->type == T_WORD)
		{
			if ((cur->value[0] == '\''
					&& cur->value[ft_strlen(cur->value) - 1] == '\'')
				|| (prev && prev->type == T_HEREDOC))
			{
				prev = cur;
				cur = cur->next;
				continue ;
			}
			expanded = expand_input(cur->value, cur, env);
			free(cur->value);
			cur->value = expanded;
		}
		prev = cur;
		cur = cur->next;
	}
}

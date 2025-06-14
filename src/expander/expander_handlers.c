/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:55:26 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/14 14:29:14 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	handle_quotes(const char *input, size_t *i, t_expand_ctx *ctx)
{
	char	*tmp;
	char	*new_result;
	char	quote_char;

	quote_char = input[*i];
	tmp = char_to_str(input[(*i)++]);
	if (quote_char == '\'')
	{
		ctx->in_single_quote = !ctx->in_single_quote;
		new_result = ft_strjoin(ctx->result, tmp);
		free(ctx->result);
		ctx->result = new_result;
	}
	else if (quote_char == '"')
	{
		ctx->in_double_quote = !ctx->in_double_quote;
		new_result = ft_strjoin(ctx->result, tmp);
		free(ctx->result);
		ctx->result = new_result;
	}
	free(tmp);
}

void	handle_dollar(const char *input, size_t *i, t_expand_ctx *ctx)
{
	char	*expanded;
	char	*tmp;
	char	*new_result;

	if (ctx->first_quote == '\'')
	{
		tmp = char_to_str(input[(*i)++]);
		new_result = ft_strjoin(ctx->result, tmp);
		free(ctx->result);
		ctx->result = new_result;
		free(tmp);
	}
	else
	{
		expanded = expand_variable(ctx, input, i);
		new_result = ft_strjoin(ctx->result, expanded);
		free(ctx->result);
		ctx->result = new_result;
		free(expanded);
	}
}

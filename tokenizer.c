/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:14 by kkoray            #+#    #+#             */
/*   Updated: 2025/04/26 12:33:15 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tokenize_segment(t_token_ctx *ctx, const char *str, int start,
		int end)
{
	if (start < end)
		add_token(ctx->head, ft_strndup(&str[start], end - start), T_WORD,
			ctx->joined);
}

static void	handle_operator(const char *input, int *i, t_token **list)
{
	int	len;

	len = operator_length(&input[*i]);
	add_token(list, ft_strndup(&input[*i], len), get_operator_type(&input[*i]),
		0);
	*i += len;
}

static void	handle_word_segment(const char *input, int *i, t_token_ctx *ctx,
		int *prev_was_space)
{
	int	start;

	while (input[*i] && input[*i] != ' ' && !is_operator_char(input[*i]))
	{
		start = *i;
		if (input[*i] == '\'' || input[*i] == '"')
			*i = read_quoted(input, *i, input[*i]);
		else
			*i = read_plain(input, *i);
		ctx->joined = (*prev_was_space == 0);
		tokenize_segment(ctx, input, start, *i);
		*prev_was_space = 0;
	}
}

t_token	*tokenize(const char *input)
{
	t_token		*list;
	int			i;
	int			prev_was_space;
	t_token_ctx	ctx;

	list = NULL;
	i = 0;
	prev_was_space = 1;
	ctx.head = &list;
	ctx.joined = 0;
	while (input[i])
	{
		i = skip_space(input, i, &prev_was_space);
		if (!input[i])
			break ;
		if (is_operator_char(input[i]))
		{
			handle_operator(input, &i, &list);
			prev_was_space = 1;
		}
		else
			handle_word_segment(input, &i, &ctx, &prev_was_space);
	}
	return (list);
}

void	free_token_list(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:14 by kkoray            #+#    #+#             */
/*   Updated: 2025/06/12 19:21:59 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	handle_operator(const char *input, int *i, t_token **list)
{
	int	len;

	len = operator_length(&input[*i]);
	add_token(list, ft_strndup(&input[*i], len), get_operator_type(&input[*i]),
		0);
	*i += len;
}

static void	handle_word_segment(const char *input, int *i, t_token_ctx *ctx, int *prev_was_space)
{
	int		start;
	int		end;
	char	*segment;

	start = *i;
	end = read_word(input, start);
	if (end <= start)
		return ;
	segment = ft_strndup(&input[start], end - start);
	if (!segment)
		return ;
	ctx->joined = (*prev_was_space == 0);
	add_token(ctx->head, segment, T_WORD, ctx->joined);
	*i = end;
	*prev_was_space = 0;
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

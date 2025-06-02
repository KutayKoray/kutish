/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_first_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:25:24 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/02 19:25:25 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	can_split_token(t_token *token)
{
	if (!token || token->next)
		return (0);
	if (token->type != T_WORD || token->trimmed)
		return (0);
	if (!ft_strchr(token->value, ' '))
		return (0);
	return (1);
}

static void apply_split(t_token *cur, char *first, char *rest)
{
	t_token	*second;

	if (first && rest)
	{
		free(cur->value);
		cur->value = first;
		second = create_token(rest, T_WORD, 0, 0);
		cur->next = second;
	}
	free(rest);
}

void	split_first_token_head_tail(t_token **tokens)
{
	t_token	*cur;
	char	*rest;
	char	*first;
	int		i;

	cur = *tokens;
	if (!can_split_token(cur))
		return ;
	i = 0;
	while (cur->value[i] == ' ')
		i++;
	while (cur->value[i] && cur->value[i] != ' ')
		i++;
	first = ft_substr(cur->value, 0, i);
	while (cur->value[i] == ' ')
		i++;
	rest = ft_strdup(&cur->value[i]);
	apply_split(cur, first, rest);
}


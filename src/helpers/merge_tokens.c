/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:43 by kkoray            #+#    #+#             */
/*   Updated: 2025/05/29 19:46:34 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

void	merge_joined_tokens(t_token **tokens)
{
	t_token	*cur;
	t_token	*next;
	char	*merged;

	cur = *tokens;
	while (cur && cur->next)
	{
		next = cur->next;
		while (next && next->type == T_WORD && next->joined == 1)
		{
			merged = ft_strjoin(ft_strdup(cur->value), next->value);
			free(cur->value);
			cur->value = merged;
			cur->next = next->next;
			free(next->value);
			free(next);
			next = cur->next;
		}
		cur = cur->next;
	}
}

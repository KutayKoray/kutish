/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded_tokens_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:03 by kkoray            #+#    #+#             */
/*   Updated: 2025/05/29 19:13:15 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

t_token	*create_token(const char *value, t_token_type type, int joined, int trimmed)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->type = type;
	new->joined = joined;
	new->trimmed = trimmed;
	new->next = NULL;
	return (new);
}

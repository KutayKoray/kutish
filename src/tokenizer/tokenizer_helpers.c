/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:08 by kkoray            #+#    #+#             */
/*   Updated: 2025/06/01 15:10:28 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	operator_length(const char *s)
{
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		return (2);
	return (1);
}

int	skip_space(const char *input, int i, int *prev_was_space)
{
	if (input[i] == ' ')
	{
		*prev_was_space = 1;
		return (i + 1);
	}
	return (i);
}

int	is_operator_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int read_word(const char *str, int start)
{
	int i = start;
	char quote;

	while (str[i] && !is_operator_char(str[i]) && str[i] != ' ')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				i++;
		}
		else
			i++;
	}
	return i;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:08 by kkoray            #+#    #+#             */
/*   Updated: 2025/05/30 14:11:54 by kkoray           ###   ########.fr       */
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

int read_quoted(const char *str, int start, char quote)
{
	int end;
	
	end = ft_strlen(str) - 1;
	while (end > start && str[end] != quote)
		end--;
	if (end <= start)
		return start + 1;
	return end + 1; 
}

int	read_plain(const char *str, int start)
{
	int	i;

	i = start;
	while (str[i] && str[i] != '\'' && str[i] != '"' && str[i] != ' '
		&& !is_operator_char(str[i]))
		i++;
	return (i);
}

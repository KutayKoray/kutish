/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:08 by kkoray            #+#    #+#             */
/*   Updated: 2025/06/12 19:12:45 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	operator_length(const char *s)
{
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		return (2);
	return (1);
}

int	skip_space(const char *input, int i, int *prev_was_space)
{
	if (input[i] == ' ' || input[i] == '\t')
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

	while (str[i] && !is_operator_char(str[i]) && str[i] != ' ' && str[i] != '\t')
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

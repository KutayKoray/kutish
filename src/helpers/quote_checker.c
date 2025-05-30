/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:54 by kkoray            #+#    #+#             */
/*   Updated: 2025/05/30 14:10:58 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

int	quote_checker(const char *input)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (input[i] == '\"' && single_quote == 0)
			double_quote = !double_quote;
		i++;
	}
	if (single_quote || double_quote)
	{
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		return (0);
	}
	return (1);
}

char	*remove_inner_matching_quotes(const char *str, char quote)
{
	int		i = 0;
	int		j = 0;
	size_t	len = ft_strlen(str);
	char	*result = malloc(len + 1);

	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != quote)
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	trim_token_quotes(t_token *tokens)
{
	t_token	*tmp;
	char	*trimmed;
	char	*cleaned;
	size_t	len;
	char	quote;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == T_WORD)
		{
			len = ft_strlen(tmp->value);
			if (len >= 2 && ((tmp->value[0] == '"' && tmp->value[len - 1] == '"')
				|| (tmp->value[0] == '\'' && tmp->value[len - 1] == '\'')))
			{
				quote = tmp->value[0];
				tmp->trimmed = 1;
				trimmed = ft_substr(tmp->value, 1, len - 2);
				if (!trimmed)
				{
					tmp = tmp->next;
					continue;
				}
				cleaned = remove_inner_matching_quotes(trimmed, quote);
				free(trimmed);
				free(tmp->value);
				tmp->value = cleaned;
			}
		}
		tmp = tmp->next;
	}
}



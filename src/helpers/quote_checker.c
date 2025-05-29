/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:54 by kkoray            #+#    #+#             */
/*   Updated: 2025/05/29 19:13:38 by kkoray           ###   ########.fr       */
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

void	trim_token_quotes(t_token *tokens)
{
	t_token	*tmp;
	char	*trimmed;
	size_t	len;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == T_WORD)
		{
			len = ft_strlen(tmp->value);
			if ((tmp->value[0] == '"' && tmp->value[len - 1] == '"')
				|| (tmp->value[0] == '\'' && tmp->value[len - 1] == '\''))
			{
				tmp->trimmed = 1;
				trimmed = ft_substr(tmp->value, 1, len - 2);
				free(tmp->value);
				tmp->value = trimmed;
			}
		}
		tmp = tmp->next;
	}
}

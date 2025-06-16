/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:31:23 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/16 17:30:41 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	quote_checker(const char *input)
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
		ft_putendl_fd("kutish: syntax error: unclosed quote", 2);
		exit_with_error(SYNTAX_ERROR, NULL, 0);
		return (0);
	}
	return (1);
}

static int	white_space_checker(const char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_input(const char *input)
{
	if (!input || !*input)
		return (0);
	if (!white_space_checker(input))
		return (0);
	if (!quote_checker(input))
		return (0);
	return (1);
}

int	pipe_redirect_check(t_token *tokens)
{
	int	prev_type;

	prev_type = T_WORD;
	if (tokens->type == T_PIPE)
		return (0);
	while (tokens)
	{
		if (tokens->type != T_WORD && prev_type != T_WORD
			&& prev_type != T_PIPE)
			return (0);
		if (tokens->type == T_PIPE && prev_type == T_PIPE)
			return (0);
		prev_type = tokens->type;
		tokens = tokens->next;
	}
	if (prev_type != T_WORD)
		return (0);
	return (1);
}

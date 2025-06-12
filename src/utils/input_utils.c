/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:31:23 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/12 19:19:10 by ebabaogl         ###   ########.fr       */
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
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		exit_with_error(SYNTAX_ERROR, NULL, 0);
		return (0);
	}
	return (1);
}

static int	pipe_checker(const char *input)
{
	char	*ptr;

	ptr = ft_strrchr(input, '|');
	if (!ptr)
		return (1);
	ptr++;
	while (ptr && *ptr)
	{
		if (*ptr != '\t' && *ptr != ' ')
			return (1);
		ptr++;
	}
	ft_putendl_fd("minishell: syntax error: empty pipe", 2);
	exit_with_error(SYNTAX_ERROR, NULL, 0);
	return (0);
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
	if (!pipe_checker(input))
		return (0);
	return (1);
}
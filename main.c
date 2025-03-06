#include "./ft_printf/ft_printf.h"
#include "libft/libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_token	*next;

	while (1)
	{
		input = readline("kutaykoray> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		tokens = NULL;
		ft_tokenize(input, &tokens);
		ft_print_tokens(tokens);
		ft_printf("------------------------------\n");
		tokens = expander(tokens);
		ft_print_tokens(tokens);
		free(input);
		while (tokens)
		{
			next = tokens->next;
			free(tokens->value);
			free(tokens);
			tokens = next;
		}
	}
	return (0);
}

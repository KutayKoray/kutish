#include "minishell.h"

#define PROMPT "minishell$ "

int	main(void)
{
	char		*input;
	t_token		*tokens;
	t_token		*tmp;

	init_signals();

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);

		if (!quote_checker(input))
		{
			free(input);
			continue;
		}

		tokens = tokenize(input);

		printf("--------------------------------\n");
		printf("Tokenizing...\n");
		tmp = tokens;
		while (tmp)
		{
			printf("Token: %-10s | Type: %d | Joined: %d\n", tmp->value, tmp->type, tmp->joined);
			tmp = tmp->next;
		}
		printf("--------------------------------\n");

		expand_token_list(tokens);

		trim_token_quotes(tokens);

		printf("--------------------------------\n");
		printf("Cleaned...\n");
		tmp = tokens;
		while (tmp)
		{
			printf("Token: %-10s | Type: %d | Joined: %d\n", tmp->value, tmp->type, tmp->joined);
			tmp = tmp->next;
		}
		printf("--------------------------------\n");

		merge_joined_tokens(&tokens);
		
		printf("--------------------------------\n");
		printf("Merged Tokens...\n");
		tmp = tokens;
		while (tmp)
		{
			printf("Token: |%s| Type: %d | Joined: %d\n", tmp->value, tmp->type, tmp->joined);
			tmp = tmp->next;
		}
		printf("--------------------------------\n");

		free_token_list(tokens);
		free(input);
	}
	return (0);
}

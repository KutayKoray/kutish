#include "minishell.h"

#define PROMPT "minishell$ "

int	main(void)
{
	char	*input;
	char	*expanded_input;

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

		expanded_input = expand_input(input);

		printf("Expanded input: %s\n", expanded_input);
		printf("%d\n", quote_checker(expanded_input));
		printf("Trimmed input: %s\n", quote_trimmer(expanded_input));

		free(expanded_input);
		free(input);
	}
	return (0);
}

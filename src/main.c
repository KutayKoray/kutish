/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:38 by kkoray            #+#    #+#             */
/*   Updated: 2025/05/01 08:57:02 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PROMPT "kutish$ "

static void print_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i, j;

	tmp = cmd;
	printf("\nCommand List:\n");
	printf("╭───────────────────────────────┬────────────────────────────────────────────╮\n");
	printf("│ %-29s │ %-42s │\n", "Field", "Value");
	printf("├───────────────────────────────┼────────────────────────────────────────────┤\n");
	while (tmp)
	{
		printf("│ %-29s │ %-42s │\n", "Command", "(argv list below)");
		if (tmp->argv)
		{
			for (i = 0; tmp->argv[i]; i++)
				printf("│   Arg[%d]                      │ %-42s │\n", i, tmp->argv[i]);
		}
		if (tmp->infile)
			printf("│ Infile                        │ %-42s │\n", tmp->infile);
		if (tmp->outfiles)
		{
			for (j = 0; tmp->outfiles[j]; j++)
				printf("│ Outfile[%d]                    │ %-42s │\n", j, tmp->outfiles[j]);
		}
		if (tmp->heredoc_eof)
			printf("│ Heredoc EOF                   │ %-42s │\n", tmp->heredoc_eof);
		printf("│ Append                        │ %-42d │\n", tmp->append);
		printf("│ Is Heredoc                    │ %-42d │\n", tmp->is_heredoc);
		if (tmp->next)
		{
			printf("├───────────────────────────────┼────────────────────────────────────────────┤\n");
			printf("│ %-29s │ %-42s │\n", "Next Command", "(linked)");
			printf("├───────────────────────────────┼────────────────────────────────────────────┤\n");
		}
		else
			printf("╰───────────────────────────────┴────────────────────────────────────────────╯\n");
		tmp = tmp->next;
	}
}

static void debug_print_cmd(t_token *tokens, char *msg)
{
	t_token *tmp;

	tmp = tokens;
	printf("\n%s\n", msg);
	printf("╭───────────────────────────────┬───────────┬──────────╮\n");
	printf("│ %-29s │ %-9s │ %-8s │\n", "Token", "Type", "Joined");
	printf("├───────────────────────────────┼───────────┼──────────┤\n");
	while (tmp)
	{
		printf("│ %-29s │ %-9d │ %-8d │\n", tmp->value, tmp->type, tmp->joined);
		tmp = tmp->next;
	}
	printf("╰───────────────────────────────┴───────────┴──────────╯\n");
}

int	main(int argc, char **argv, char **envp)
{
	int		debug;
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;

	(void)argc;
	(void)envp;
	debug = (argv[1] && !ft_strncmp(argv[1], "-d", 2));
	init_signals();
	if (debug)
		printf("you're currently in debug mode, each step will be displayed.\n");
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
		if (debug)
			debug_print_cmd(tokens, "Tokenizing...");
		expand_token_list(tokens);
		if (debug)
			debug_print_cmd(tokens, "Expanded...");
		trim_token_quotes(tokens);
		if (debug)
			debug_print_cmd(tokens, "Trimmed...");
		split_expanded_tokens(&tokens);
		if (debug)
			debug_print_cmd(tokens, "Splitted...");
		merge_joined_tokens(&tokens);
		if (debug)
			debug_print_cmd(tokens, "Merged...");
		cmds = parse_tokens(tokens);
		if (debug)
			print_cmd_list(cmds);

		free_cmd_list(cmds);
		free_token_list(tokens);
		free(input);
	}
	return (0);
}

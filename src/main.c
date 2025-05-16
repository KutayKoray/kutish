/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:38 by kkoray            #+#    #+#             */
/*   Updated: 2025/05/16 12:05:23 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PROMPT "kutish$ "

static char	*prettify_buffer(char *buffer)
{
	char	*tmp;
	int		i;

	tmp = malloc(sizeof(char) * (ft_strlen(buffer) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			tmp[i] = '\\';
		else
			tmp[i] = buffer[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

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
		{
			int k = 0;
			while (tmp->heredoc_eof[k])
			{
				printf("│ Heredoc[%d]                    │ %-42s │\n", k, tmp->heredoc_eof[k]);
				k++;
			}
		}
		printf("│ Append                        │ %-42d │\n", tmp->append);
		printf("│ Is Heredoc                    │ %-42d │\n", tmp->is_heredoc);
		if (tmp->is_heredoc)
			printf("│ Heredoc Expand                │ %-42d │\n", tmp->heredoc_expand);
		if (tmp->heredoc_buffer)
			printf("│ Heredoc Buffer                │ %-42s │\n", prettify_buffer(tmp->heredoc_buffer));
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
	printf("╭───────────────────────────────┬───────────┬──────────┬───────────╮\n");
	printf("│ %-29s │ %-9s │ %-8s │ %-9s │\n", "Token", "Type", "Joined", "Trimmed");
	printf("├───────────────────────────────┼───────────┼──────────┼───────────┤\n");
	while (tmp)
	{
		printf("│ %-29s │ %-9d │ %-8d │ %-9d │\n",
			tmp->value, tmp->type, tmp->joined, tmp->trimmed);
		tmp = tmp->next;
	}
	printf("╰───────────────────────────────┴───────────┴──────────┴───────────╯\n");
}

static void	assign_heredoc_buffers(t_cmd *cmds, t_env *env)
{
	t_cmd	*cur;
	char	*raw;

	cur = cmds;
	while (cur)
	{
		if (cur->is_heredoc)
		{
			raw = get_heredoc(cur);
			if (!raw)
				return ;
			if (cur->heredoc_expand)
				cur->heredoc_buffer = expand_input(raw, env);
			else
				cur->heredoc_buffer = raw;
			// free(raw);
		}
		cur = cur->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		debug;
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
	t_env	*env;

	(void)argc;
	init_signals();
	env = init_env(envp);
	
	debug = (argv[1] && !ft_strncmp(argv[1], "-d", 2));
	if (debug)
	{
		printf("you're currently in debug mode, each step will be displayed.\n");
		// print_env(env);
	}
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
		expand_token_list(tokens, env);
		if (debug)
			debug_print_cmd(tokens, "Expanded...");
		trim_token_quotes(tokens);
		if (debug)
			debug_print_cmd(tokens, "Trimmed...");
		split_first_token_head_tail(&tokens);
		if (debug)
			debug_print_cmd(tokens, "Echo Split...");
		// split_expanded_tokens(&tokens);
		// if (debug)
		// 	debug_print_cmd(tokens, "Splitted...");
		// merge_joined_tokens(&tokens);
		// if (debug)
		// 	debug_print_cmd(tokens, "Merged...");
		cmds = parse_tokens(tokens);
		if (debug)
			print_cmd_list(cmds);
		assign_heredoc_buffers(cmds, env);
		if (debug)
			print_cmd_list(cmds);

		free_cmd_list(cmds);
		free_token_list(tokens);
		free(input);
	}
	free_env(env);
	return (0);
}

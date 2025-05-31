/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:04:41 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/31 14:01:49 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "tokenizer.h"
#include "parser.h"
#include "helpers.h"
#include "expander.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_cmd	*cmd;
	int		debug;
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	env = init_env_list(envp);
	initialize_envs(&env);
	get_env_head(env);

	cmds = create_cmd();
	cmds->argv = ft_calloc(3, sizeof(char *));
	cmds->argv[0] = ft_strdup("echo");
	cmds->argv[1] = ft_strdup("-la");
	cmds->next = create_cmd();
	cmds->next->argv = ft_calloc(2, sizeof(char *));
	cmds->next->argv[0] = ft_strdup("pwd");
	cmds->next->next = create_cmd();
	cmds->next->next->argv = ft_calloc(3, sizeof(char *));
	cmds->next->next->argv[0] = ft_strdup("exit");
	cmds->next->next->next = NULL;
	get_cmd_head(cmds);
	execute_pipeline(cmds, &env);
	free_lists();

	// debug = (argv[1] && !ft_strncmp(argv[1], "-d", 2));
	// if (debug)
	// 	printf("you're currently in debug mode, each step will be displayed.\n");
	// while (1)
	// {
	// 	input = readline(PROMPT);
	// 	if (!input)
	// 	{
	// 		printf("exit\n");
	// 		break;
	// 	}
	// 	if (*input)
	// 		add_history(input);
	// 	else
	// 	{
	// 		free(input);
	// 		continue;
	// 	}
	// 	if (!quote_checker(input))
	// 	{
	// 		free(input);
	// 		continue;
	// 	}

	// 	tokens = tokenize(input);
	// 	if (debug)
	// 		debug_print_cmd(tokens, "Tokenizing...");
	// 	expand_token_list(tokens, env);
	// 	if (debug)
	// 		debug_print_cmd(tokens, "Expanded...");
	// 	trim_token_quotes(tokens);
	// 	if (debug)
	// 		debug_print_cmd(tokens, "Trimmed...");
	// 	split_first_token_head_tail(&tokens);
	// 	if (debug)
	// 		debug_print_cmd(tokens, "Echo Split...");
	// 	// split_expanded_tokens(&tokens);
	// 	// if (debug)
	// 	// 	debug_print_cmd(tokens, "Splitted...");
	// 	// merge_joined_tokens(&tokens);
	// 	// if (debug)
	// 	// 	debug_print_cmd(tokens, "Merged...");
	// 	cmds = parse_tokens(tokens);
	// 	if (debug)
	// 		print_cmd_list(cmds);
	// 	assign_heredoc_buffers(cmds, env);
	// 	if (debug)
	// 		print_cmd_list(cmds);
	// 	execute_pipeline(cmds, &env);
	// 	free_cmd_list(cmds);
	// 	free_token_list(tokens);
	// 	free(input);
	// }
	// free_env_list(env);
	return (0);
}

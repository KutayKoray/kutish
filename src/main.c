/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:04:41 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/02 20:21:11 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	repl(t_token **tokens, t_env **env, t_cmd **cmds, int debug)
{
	char	*input;

	set_signal_handler(0);
	input = readline(PROMPT);
	if (!input)
		return (0);
	if (*input && is_valid_input(input))
	{
		add_history(input);
		*tokens = tokenize(input);
		if (debug)
			debug_print_cmd(*tokens, "tokenizing");
		expand_token_list(*tokens, *env);
		if (debug)
			debug_print_cmd(*tokens, "expanding");
		trim_token_quotes(*tokens);
		if (debug)
			debug_print_cmd(*tokens, "trimming quotes");
		split_first_token_head_tail(tokens);
		if (debug)
			debug_print_cmd(*tokens, "splitting first token");
		*cmds = parse_tokens(*tokens, *env);
		if (debug)
			debug_print_cmd(*tokens, "parsing tokens");
		get_cmd_head(*cmds);
		free_token_list(*tokens);
		if (*cmds && (*cmds)->argv)
			execute_pipeline(*cmds, env);
		free_cmd_list(*cmds);
	}
	free(input);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*tokens;
	t_env	*env;
	t_cmd	*cmds;
	int		debug;

	(void)argc;
	env = init_env_list(envp);
	initialize_envs(&env);
	get_env_head(env);
	debug = (argv[1] && !ft_strncmp(argv[1], "-d", 3));
	while (1)
	{
		if (!repl(&tokens, &env, &cmds, debug))
			break ;
	}
	free_env_list(env);
	return (0);
}

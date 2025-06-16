/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:04:41 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/16 16:31:35 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static void	process_tokens(char *input, t_token **tokens, t_env *env,
	int debug)
{
	*tokens = tokenize(input);
	free(input);
	if (debug)
		debug_print_cmd(*tokens, "tokenizing");
	expand_token_list(tokens, env);
	if (debug)
		debug_print_cmd(*tokens, "expanding");
	trim_token_quotes(*tokens);
	if (debug)
		debug_print_cmd(*tokens, "trimming quotes");
	split_expanded_tokens(tokens);
	if (debug)
		debug_print_cmd(*tokens, "splitting expanded tokens");
}

static void	parse_and_execute(t_token *tokens, t_env **env, t_cmd **cmds,
	int debug)
{
	*cmds = parse_tokens(tokens, *env);
	if (debug)
		debug_print_cmd(tokens, "parsing tokens");
	free_token_list(tokens);
	get_cmd_head(*cmds);
	if (debug)
		print_cmd_list(*cmds);
	if (*cmds && (*cmds)->argv && !g_signal)
		execute_pipeline(*cmds, env);
	else if (*cmds && !(*cmds)->argv)
	{
		ft_putendl_fd("kutish: : command not found", 2);
		exit_with_error(EX_NOTFOUND, NULL, 0);
	}
}

static int	read_and_execute(t_token **tokens, t_env **env, t_cmd **cmds,
	int debug)
{
	char	*input;

	set_signal_handler(0);
	input = readline(PROMPT);
	if (!input)
		return (0);
	if (!*input || !is_valid_input(input))
	{
		free(input);
		return (1);
	}
	add_history(input);
	process_tokens(input, tokens, *env, debug);
	if (!*tokens)
	{
		exit_with_error(EXECUTION_SUCCESS, NULL, 0);
		return (1);
	}
	parse_and_execute(*tokens, env, cmds, debug);
	free_cmd_list(*cmds);
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
		if (!read_and_execute(&tokens, &env, &cmds, debug))
			break ;
	}
	free_env_list(env);
	return (0);
}

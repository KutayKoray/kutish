/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:04:41 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/25 18:22:37 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "exec.h"
#include <stdlib.h>

#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_cmd	cmd;

	(void)argc;
	(void)argv;
	env = init_env_list(envp);
	if (!env)
		return (EXIT_FAILURE);

	cmd.argv = (char *[]){"builtin", "a", NULL};
	cmd.outfiles = NULL;
	cmd.infile = "input";
	cmd.heredoc_eof = NULL;
	cmd.heredoc_buffer = NULL;
	cmd.append = 0;
	cmd.is_heredoc = 0;
	cmd.next = NULL;

	execute_pipeline(&cmd, env);

	// char *path = get_cmd_path(argv[1], env);
	// printf("%s.\n", path);

	free_env_list(env);
	// return (*exit_status());
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:04:41 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/25 14:28:23 by ebabaogl         ###   ########.fr       */
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
	t_cmd	cmd, cmd2, cmd3, cmd4;

	(void)argc;
	(void)argv;
	env = init_env_list(envp);
	if (!env)
		return (EXIT_FAILURE);

	cmd.argv = (char *[]){"ls", "-la", NULL};
	cmd.outfiles = NULL;
	cmd.infile = NULL;
	cmd.heredoc_eof = NULL;
	cmd.heredoc_buffer = NULL;
	cmd.append = 0;
	cmd.is_heredoc = 0;
	cmd.next = &cmd2;

	cmd2.argv = (char *[]){"cat", NULL};
	cmd2.outfiles = NULL;
	cmd2.infile = NULL;
	cmd2.heredoc_eof = NULL;
	cmd2.heredoc_buffer = NULL;
	cmd2.append = 0;
	cmd2.is_heredoc = 0;
	cmd2.next = &cmd3;

	cmd3.argv = (char *[]){"grep", "Make", NULL};
	cmd3.outfiles = NULL;
	cmd3.infile = NULL;
	cmd3.heredoc_eof = NULL;
	cmd3.heredoc_buffer = NULL;
	cmd3.append = 0;
	cmd3.is_heredoc = 0;
	cmd3.next = &cmd4;

	cmd4.argv = (char *[]){"wc", "-l", NULL};
	cmd4.outfiles = NULL;
	cmd4.infile = NULL;
	cmd4.heredoc_eof = NULL;
	cmd4.heredoc_buffer = NULL;
	cmd4.append = 0;
	cmd4.is_heredoc = 0;
	cmd4.next = NULL;

	execute_pipeline(&cmd, env);

	// char *path = get_cmd_path(argv[1], env);
	// printf("%s.\n", path);

	free_env_list(env);
	return (0);
}

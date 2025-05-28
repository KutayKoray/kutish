/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:04:41 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/28 14:25:49 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_cmd	cmd;

	(void)argc;
	(void)argv;
	env = init_env_list(envp);
	initialize_envs(&env);

	cmd.argv = (char *[]){"export", NULL};
	cmd.outfiles = NULL;
	cmd.infile = NULL;
	cmd.heredoc_eof = NULL;
	cmd.heredoc_buffer = NULL;
	cmd.append = 0;
	cmd.is_heredoc = 0;
	cmd.next = NULL;
	execute_pipeline(&cmd, &env);

	free_env_list(env);
	return (*exit_status());
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:04:41 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/29 01:29:08 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	env = init_env_list(envp);
	initialize_envs(&env);

	cmd = malloc(sizeof(t_cmd));
	cmd->argv = malloc(sizeof(char *) * 3);
	cmd->argv[0] = ft_strdup("ls");
	cmd->argv[1] = ft_strdup("-la");
	cmd->argv[2] = NULL;
	cmd->outfiles = NULL;
	cmd->infile = NULL;
	cmd->heredoc_eof = NULL;
	cmd->heredoc_buffer = NULL;
	cmd->append = 0;
	cmd->is_heredoc = 0;
	cmd->next = NULL;

	execute_pipeline(cmd, &env);
	free_lists(cmd, env);
	return (*exit_status());
}

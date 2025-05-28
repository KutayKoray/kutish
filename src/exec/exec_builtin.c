/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:22:26 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/28 18:58:56 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

static int	exec_builtin(t_cmd *cmd, t_env **env)
{
	int	exit_code;

	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		exit_code = echo_builtin(cmd->argv);
	else if (!ft_strncmp(cmd->argv[0], "export", 7))
		exit_code = export_builtin(cmd->argv, env);
	return (exit_code);
}

/**
 * Handles the execution of built-in commands.
 * If the command is a built-in and has no next command, it executes it.
 * It also handles input/output redirection for the built-in command.
 *
 * @param cmd The command to execute.
 * @param env The environment variables.
 * @param pipe_info The pipe information for redirection.
 * @return 0 on success, or a status code indicating failure.
 */
int	handle_builtin(t_cmd *cmd, t_env **env, t_pipe_info *pipe_info)
{
	int	status;

	status = 0;
	if (cmd->next || !is_builtin(cmd->argv[0]))
		return (status);
	pipe_info->original_stdin = dup(STDIN_FILENO);
	pipe_info->original_stdout = dup(STDOUT_FILENO);
	status = outfile_redirection(cmd, pipe_info)
		& infile_redirection(cmd, pipe_info);
	*exit_status() = exec_builtin(cmd, env);
	dup2(pipe_info->original_stdin, STDIN_FILENO);
	dup2(pipe_info->original_stdout, STDOUT_FILENO);
	close(pipe_info->original_stdin);
	close(pipe_info->original_stdout);
	return (status);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:22:26 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/16 17:24:16 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

static int	exec_builtin(t_cmd *cmd, t_env **env)
{
	int	exit_code;

	exit_code = 1;
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		exit_code = echo_builtin(cmd->argv);
	else if (!ft_strncmp(cmd->argv[0], "export", 7))
		exit_code = export_builtin(cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "unset", 6))
		exit_code = unset_builtin(cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		exit_code = pwd_builtin();
	else if (!ft_strncmp(cmd->argv[0], "env", 4))
		exit_code = env_builtin(*env);
	else if (!ft_strncmp(cmd->argv[0], "cd", 3))
		exit_code = cd_builtin(cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "exit", 5))
		exit_code = exit_builtin(cmd);
	return (exit_code);
}

void	handle_builtin(t_cmd *cmd, t_env **env)
{
	int	status;

	if (!is_builtin(cmd->argv[0]))
		return ;
	status = exec_builtin(cmd, env);
	free_lists();
	exit_with_error(status, NULL, 1);
}

int	handle_single_builtin(t_cmd *cmd, t_env **env, t_pipe_info *pipe_info)
{
	int	status;
	int	exit_code;

	status = 0;
	if (cmd->next || !cmd->argv || !is_builtin(cmd->argv[0]))
		return (status);
	pipe_info->original_stdin = dup(STDIN_FILENO);
	pipe_info->original_stdout = dup(STDOUT_FILENO);
	status = outfile_redirection(cmd)
		& infile_redirection(cmd, pipe_info);
	exit_code = exec_builtin(cmd, env);
	exit_with_error(exit_code, NULL, 0);
	dup2(pipe_info->original_stdin, STDIN_FILENO);
	dup2(pipe_info->original_stdout, STDOUT_FILENO);
	close(pipe_info->original_stdin);
	close(pipe_info->original_stdout);
	return (status);
}

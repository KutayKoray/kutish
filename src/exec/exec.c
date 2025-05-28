/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:51:28 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/28 18:44:42 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

static void	exec_cmd(t_cmd *cmd, t_env *env)
{
	char	*cmd_path;
	char	**envp;

	if (!*cmd->argv)
		exit(EXECUTION_SUCCESS);
	cmd_path = get_cmd_path(cmd->argv[0], env);
	if (!cmd_path)
		exit_nocmd(cmd->argv[0], 1);
	envp = env2envp(env);
	if (!envp)
	{
		free(cmd_path);
		exit_with_error(EXECUTION_FAILURE, SHELL_NAME, 1);
	}
	execve(cmd_path, cmd->argv, envp);
	free(cmd_path);
	free_str_arr(envp);
	exit_with_error(EX_NOEXEC, SHELL_NAME, 1);
}

static int	set_redirections(t_cmd *cmd, t_pipe_info *pipe_info)
{
	if (cmd->next)
	{
		dup2(pipe_info->pipe_fd[1], STDOUT_FILENO);
		close(pipe_info->pipe_fd[0]);
		close(pipe_info->pipe_fd[1]);
	}
	if (!outfile_redirection(cmd, pipe_info) || !infile_redirection(cmd, pipe_info))
	{
		// free structs
		return (0);
	}
	return (1);
}

// bash kkill pipeline with EX_NOEXEC exit code if fork fails, here is the reference:
// https://github.com/bminor/bash/blob/6794b5478f660256a1023712b5fc169196ed0a22/jobs.c#L2199
static pid_t	create_process(t_cmd *cmd, t_env **env, t_pipe_info *pipe_info)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		if (cmd->next)
		{
			close(pipe_info->pipe_fd[0]);
			close(pipe_info->pipe_fd[1]);
		}
		if (pipe_info->fd_in != STDIN_FILENO)
			close(pipe_info->fd_in);
		return (exit_with_error(EX_NOEXEC, SHELL_NAME, 0), -1);
	}
	else if (pid == 0)
	{
		if (!set_redirections(cmd, pipe_info))
			exit_with_error(EXECUTION_FAILURE, SHELL_NAME, 1);
		exec_cmd(cmd, *env);
	}
	return (pid);
}

void	execute_pipeline(t_cmd *cmd, t_env **env)
{
	t_pipe_info	pipe_info;
	pid_t		last_pid;

	last_pid = -1;
	pipe_info.fd_in = STDIN_FILENO;
	if (handle_builtin(cmd, env, &pipe_info))
		return ;
	while (cmd)
	{
		if (cmd->next && !create_pipe(pipe_info.pipe_fd))
			break ;
		last_pid = create_process(cmd, env, &pipe_info);
		if (last_pid == -1) // fork fail
			break ;
		if (pipe_info.fd_in != STDIN_FILENO)
			close(pipe_info.fd_in);
		if (cmd->next)
		{
			close(pipe_info.pipe_fd[1]);
			pipe_info.fd_in = pipe_info.pipe_fd[0];
		}
		cmd = cmd->next;
	}
	wait_for_pipeline(last_pid);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:51:28 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/30 11:07:14 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

// buradan direkt cikis yapma, freeleri unutma
// get_cmd_path de ayni unutma
static void	exec_cmd(t_cmd *cmd, t_env *env)
{
	char	*cmd_path;
	char	**envp;

	cmd_path = get_cmd_path(cmd, env);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_lists(cmd, env);
		exit_with_error(EX_NOTFOUND, NULL, 1);
	}
	envp = env2envp(env);
	if (!envp)
	{
		free(cmd_path);
		free_lists(cmd, env);
		exit_with_error(EXECUTION_FAILURE, NULL, 1);
	}
	execve(cmd_path, cmd->argv, envp);
	free(cmd_path);
	free_str_arr(envp);
	free_lists(cmd, env);
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
	if (!outfile_redirection(cmd, pipe_info)
		|| !infile_redirection(cmd, pipe_info))
		return (0);
	return (1);
}

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
		return (exit_with_error(EX_NOEXEC, NULL, 0), -1);
	}
	else if (pid == 0)
	{
		if (!set_redirections(cmd, pipe_info))
		{
			free_lists(cmd, *env);
			exit_with_error(EXECUTION_FAILURE, NULL, 1);
		}
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
		if (last_pid == -1)
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

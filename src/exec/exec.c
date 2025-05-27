/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:06:04 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/27 16:23:43 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"
#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

static void	wait_for_pipeline(pid_t last_pid)
{
	int	status;

	if (last_pid == -1)
		return ;
	if (waitpid(last_pid, &status, 0) == -1)
	{
		exit_with_error(EXECUTION_FAILURE, SHELL_NAME, 0);
		return ;
	}
	*exit_status() = WEXITSTATUS(status);
	while (wait(NULL) > 0)
		;
}

static void	execute_cmd(t_cmd *cmd, t_env *env)
{
	char	*cmd_path;
	char	**envp;

	if (!*cmd->argv)
		exit(EXECUTION_SUCCESS);
	cmd_path = get_cmd_path(cmd->argv[0], env);
	if (!cmd_path)
		exit_with_error(EX_NOTFOUND, SHELL_NAME, 1);
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

static void	handle_builtin(t_cmd *cmd, t_env **env)
{
	int	original_stdin;
	int	original_stdout;
	int	fd_in;
	int	exit_code;

	fd_in = STDIN_FILENO;
	if (!outfile_redirects(cmd, NULL, 1, &original_stdout))
		return ;
	if (!infile_redirects(cmd, &fd_in, 1, &original_stdin))
		return ;
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		exit_code = echo_builtin(cmd->argv);
	else if (!ft_strncmp(cmd->argv[0], "export", 7))
		exit_code = export_builtin(cmd->argv, env);
	// else if (!ft_strncmp(cmd->argv[0], "cd", 3))
	// else if ...
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	*exit_status() = exit_code;
}

// bash exit with EX_NOEXEC if fork fails, here is the reference:
// https://github.com/bminor/bash/blob/6794b5478f660256a1023712b5fc169196ed0a22/jobs.c#L2199
static int	create_process(t_cmd *cmd, t_env *env, int *fd, int *fd_in)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (exit_with_error(EX_NOEXEC, SHELL_NAME, 0), -1);
	else if (pid == 0)
	{
		outfile_redirects(cmd, fd, 0, NULL);
		infile_redirects(cmd, fd_in, 0, NULL);
		execute_cmd(cmd, env);
	}
	return (pid);
}

void	execute_pipeline(t_cmd *cmd, t_env **env)
{
	pid_t	last_pid;
	int		fd[2];
	int		fd_in;

	last_pid = -1;
	fd_in = STDIN_FILENO;
	if (!cmd->next && is_builtin(cmd->argv[0]))
	{
		handle_builtin(cmd, env);
		return ;
	}
	while (cmd)
	{
		if (cmd->next && !create_pipe(fd))
			break ;
		last_pid = create_process(cmd, *env, fd, &fd_in);
		if (last_pid == -1)
		{
			if (cmd->next)
			{
				close(fd[0]);
				close(fd[1]);
			}
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			break;
		}
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (cmd->next)
		{
			close(fd[1]);
			fd_in = fd[0];
		}
		cmd = cmd->next;
	}
	wait_for_pipeline(last_pid);
}

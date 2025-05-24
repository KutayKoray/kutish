/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:06:04 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/24 23:22:24 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
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
		exit_with_error(EXIT_GENERIC_ERR, "kutish", 0);
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

	cmd_path = get_cmd_path(cmd->argv[0], env);
	if (!cmd_path)
		exit_with_error(EXIT_NO_CMD, "kutish", 1);
	envp = env2envp(env);
	if (!envp)
	{
		free(cmd_path);
		exit_with_error(EXIT_GENERIC_ERR, "kutish", 1);
	}
	execve(cmd_path, cmd->argv, envp);
	free(cmd_path);
	free_str_arr(envp);
	exit_with_error(EXIT_CANNOT_EXEC, "kutish", 1);
}

static int	create_process(t_cmd *cmd, t_env *env, int *fd, int *fd_in)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (exit_with_error(EXIT_GENERIC_ERR, "kutish", 0), -1);
	else if (pid == 0)
	{
		outfile_redirects(cmd, fd);
		infile_redirects(cmd, fd_in);
		execute_cmd(cmd, env);
	}
	return (pid);
}

void	execute_pipeline(t_cmd *cmd, t_env *env)
{
	pid_t	last_pid;
	int		fd[2];
	int		fd_in;

	last_pid = -1;
	fd_in = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next && !create_pipe(fd))
			break ;
		last_pid = create_process(cmd, env, fd, &fd_in);
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

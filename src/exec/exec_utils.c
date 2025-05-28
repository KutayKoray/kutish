/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:08:32 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/28 18:50:36 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Checks if the command is a built-in command.
 *
 * This function compares the given command against a list of known
 * built-in commands. If a match is found, it returns 1, indicating
 * that the command is a built-in. Otherwise, it returns 0.
 *
 * @param cmd Command to check.
 * @return 1 if the command is a built-in, 0 otherwise.
 */
int	is_builtin(char *cmd)
{
	char	*builtins[] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL
	};
	size_t	i;

	i = 0;
	while (builtins[i])
	{
		if (!ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i]) + 1))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Creates a pipe and initializes the file descriptors.
 *
 * This function creates a pipe and stores the file descriptors in the
 * provided array. If the pipe creation fails, it exits with an error.
 *
 * @param fd Pointer to an array of two integers where the pipe file descriptors will be stored.
 * @return 1 on success, 0 on failure.
 */
int	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
		return (exit_with_error(EXECUTION_FAILURE, SHELL_NAME, 0), 0);
	return (1);
}

/**
 * @brief Waits for the last process in a pipeline to finish and cleans up.
 *
 * This function waits for the last process in a pipeline to complete,
 * retrieves its exit status, and cleans up any remaining child processes.
 *
 * @param last_pid The PID of the last process in the pipeline.
 */
void	wait_for_pipeline(pid_t last_pid)
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
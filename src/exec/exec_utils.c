/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:36:57 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/27 20:39:47 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * @brief Returns a pointer to a static exit status variable.
 *
 * This function provides access to a static integer used to store
 * the last command's exit status. It allows other parts of the
 * program to read or modify the exit status without using a global
 * variable directly.
 *
 * @return Pointer to the static integer representing the exit status.
 */
int		*exit_status(void)
{
	static int	status = 0;

	return (&status);
}

/**
 * @brief Creates a pipe and stores file descriptors in the provided array.
 *
 * This function attempts to create a pipe using the `pipe` system call.
 * If successful, it stores the read and write file descriptors in the
 * provided array. If it fails, it prints an error message and sets the
 * exit status.
 *
 * @param fd Array to store the read and write file descriptors.
 * @return 1 on success, 0 on failure.
 */
int	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
		return (exit_with_error(EXECUTION_FAILURE, SHELL_NAME, 0), 0);
	return (1);
}

/**
 * @brief Handles errors by printing a message and optionally exiting.
 *
 * This function prints an error message to stderr, sets the exit status,
 * and either exits the program or returns based on the is_exit flag.
 *
 * @param status Exit status to set.
 * @param message Error message to print.
 * @param is_exit If true, exits the program; otherwise, just returns.
 */
void	exit_with_error(int status, const char *message, int is_exit) 
{
	perror(message);
	*exit_status() = status;
	if (is_exit)
		exit(status);
	else
		return ;
}

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
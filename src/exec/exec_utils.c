/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:36:57 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/25 15:26:04 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

int	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
		return (exit_with_error(EXECUTION_FAILURE, SHELL_NAME, 0), 0);
	return (1);
}

void	exit_with_error(int status, const char *message, int is_exit) 
{
	perror(message);
	*exit_status() = status;
	if (is_exit)
		exit(status);
	else
		return ;
}

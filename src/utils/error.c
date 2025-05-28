/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:47:52 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/29 01:37:02 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
 * @brief Exits the program with a specified status and an optional error message.
 *
 * This function prints an error message to standard error if provided,
 * sets the exit status, and then either exits the program or returns
 * based on the is_exit flag.
 *
 * @param status The exit status to set.
 * @param message An optional error message to print.
 * @param is_exit A flag indicating whether to exit the program (1) or return (0).
 */
void	exit_with_error(int status, const char *message, int is_exit) 
{
	if (message)
		perror(message);
	*exit_status() = status;
	if (is_exit)
		exit(status);
	else
		return ;
}
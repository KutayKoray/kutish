/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:47:52 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/28 18:44:05 by ebabaogl         ###   ########.fr       */
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

void	exit_nocmd(char *cmd, int is_exit)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit_with_error(EX_NOEXEC, NULL, is_exit);
}

void	exit_isadir(char *cmd, int is_exit)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	exit_with_error(EX_NOEXEC, NULL, is_exit);
}

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
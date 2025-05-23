/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:06:04 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/23 16:54:18 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <sys/types.h>
#include <unistd.h>

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

void	execute_pipeline(t_cmd *cmd, t_env *env)
{
	(void)cmd;
	(void)env;
}
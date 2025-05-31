/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:47:52 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/31 13:59:04 by ebabaogl         ###   ########.fr       */
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
int	*exit_status(void)
{
	static int	status = 0;

	return (&status);
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

t_cmd	**get_cmd_head(t_cmd *cmd)
{
	static t_cmd	*head = NULL;

	if (cmd)
		head = cmd;
	return (&head);
}

t_env	**get_env_head(t_env *env)
{
	static t_env	*head = NULL;

	if (env)
		head = env;
	return (&head);
}

void	free_lists(void)
{
	t_cmd	**cmd_head;
	t_env	**env_head;

	cmd_head = get_cmd_head(NULL);
	if (*cmd_head)
	{
		free_cmd_list(*cmd_head);
		*cmd_head = NULL;
	}
	env_head = get_env_head(NULL);
	if (*env_head)
	{
		free_env_list(*env_head);
		*env_head = NULL;
	}
}

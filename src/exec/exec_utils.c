/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:08:32 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/12 18:58:39 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "exit", 5)
		|| !ft_strncmp(cmd, "export", 7) || !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "unset", 6))
		return (1);
	return (0);
}

int	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
		return (exit_with_error(EXECUTION_FAILURE, SHELL_NAME, 0), 0);
	return (1);
}

void	wait_for_pipeline(pid_t last_pid)
{
	int	status;

	if (last_pid == -1)
		return ;
	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		exit_with_error(WEXITSTATUS(status), NULL, 0);
	else
		exit_with_error(WTERMSIG(status) + 128, NULL, 0);
	while (wait(NULL) > 0)
		;
}

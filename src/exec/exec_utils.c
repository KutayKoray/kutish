/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:08:32 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/29 01:45:43 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

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
	if (waitpid(last_pid, &status, 0) == -1)
	{
		exit_with_error(EXECUTION_FAILURE, SHELL_NAME, 0);
		return ;
	}
	*exit_status() = WEXITSTATUS(status);
	while (wait(NULL) > 0)
		;
}

void	free_lists(t_cmd *cmd, t_env *env)
{
	t_cmd	*tmp_cmd;
	t_env	*tmp_env;

	while (env)
	{
		tmp_env = env;
		env = env->next;
		free(tmp_env->key);
		free(tmp_env->value);
		free(tmp_env);
	}
	while (cmd)
	{
		tmp_cmd = cmd;
		cmd = cmd->next;
		free_str_arr(tmp_cmd->argv);
		free_str_arr(tmp_cmd->outfiles);
		free(tmp_cmd->infile);
		free_str_arr(tmp_cmd->heredoc_eof);
		free(tmp_cmd->heredoc_buffer);
		free(tmp_cmd);
	}
}

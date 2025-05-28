/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:52:49 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/28 14:25:29 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_redirects(t_cmd *cmd, int *fd_in, int is_single_builtin, int *original_stdin)
{
	int	hd_fd[2];

	if (is_single_builtin)
		*original_stdin = dup(STDIN_FILENO);
	if (cmd->is_heredoc && cmd->heredoc_buffer)
	{
		if (!create_pipe(hd_fd))
			exit(EXECUTION_FAILURE);
		write(hd_fd[1], cmd->heredoc_buffer, ft_strlen(cmd->heredoc_buffer));
		close(hd_fd[1]);
		dup2(hd_fd[0], STDIN_FILENO);
		close(hd_fd[0]);
	}
	else if (cmd->infile)
	{
		*fd_in = open(cmd->infile, O_RDONLY);
		if (*fd_in == -1)
			return (exit_with_error(EXECUTION_FAILURE, SHELL_NAME, !is_single_builtin), 0);
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	else if (*fd_in != STDIN_FILENO)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	return (1);
}

int	outfile_redirects(t_cmd *cmd, int *pipe_fd, int is_single_builtin, int *original_stdout)
{
	size_t	i;
	int		fd;

	if (is_single_builtin)
		*original_stdout = dup(STDOUT_FILENO);
	if (cmd->next && !is_single_builtin)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	i = 0;
	if (!cmd->outfiles || !*cmd->outfiles)
		return (1);
	while (cmd->outfiles[i])
	{
		fd = open(cmd->outfiles[i], O_CREAT, 0644);
		if (fd == -1)
			return (exit_with_error(EXECUTION_FAILURE, SHELL_NAME, !is_single_builtin), 0);
		close(fd);
		i++;
	}
	if (cmd->append)
		fd = open(cmd->outfiles[i - 1], O_WRONLY | O_APPEND);
	else
		fd = open(cmd->outfiles[i - 1], O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (exit_with_error(EXECUTION_FAILURE, SHELL_NAME, !is_single_builtin), 0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

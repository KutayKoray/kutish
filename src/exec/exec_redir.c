/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:52:50 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/28 18:51:41 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Redirects the output for a command.
 *
 * This function handles output redirection for a command, either to a file
 * or appending to an existing file. It sets up the necessary file descriptors
 * and duplicates them to standard output.
 *
 * @param cmd The command structure containing output redirection information.
 * @param pipe_info The pipe information structure containing file descriptors.
 * @return 1 on success, 0 on failure.
 */
int	outfile_redirection(t_cmd *cmd, t_pipe_info *pipe_info)
{
	size_t	i;
	int		fd;

	i = 0;
	if (!cmd->outfiles || !*cmd->outfiles)
		return (1);
	while (cmd->outfiles[i])
	{
		fd = open(cmd->outfiles[i], O_CREAT, 0644);
		if (fd == -1)
			return (0);
		close(fd);
		i++;
	}
	if (cmd->append)
		fd = open(cmd->outfiles[i - 1], O_WRONLY | O_APPEND);
	else
		fd = open(cmd->outfiles[i - 1], O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

/**
 * @brief Redirects the input for a command.
 *
 * This function handles input redirection for a command, either from a
 * heredoc buffer or an input file. It sets up the necessary file descriptors
 * and duplicates them to standard input.
 *
 * @param cmd The command structure containing input redirection information.
 * @param pipe_info The pipe information structure containing file descriptors.
 * @return 1 on success, 0 on failure.
 */
int	infile_redirection(t_cmd *cmd, t_pipe_info *pipe_info)
{
	int	hd_fd[2];

	if (cmd->is_heredoc && cmd->heredoc_buffer)
	{
		if (!create_pipe(hd_fd))
			return (0); // exit with EXECUTION_FAILURE
		write(hd_fd[1], cmd->heredoc_buffer, ft_strlen(cmd->heredoc_buffer));
		close(hd_fd[1]);
		dup2(hd_fd[0], STDIN_FILENO);
		close(hd_fd[0]);
	}
	else if (cmd->infile)
	{
		pipe_info->fd_in = open(cmd->infile, O_RDONLY);
		if (pipe_info->fd_in == -1)
			return (0);
		dup2(pipe_info->fd_in, STDIN_FILENO);
		close(pipe_info->fd_in);
	}
	else if (pipe_info->fd_in != STDIN_FILENO)
	{
		dup2(pipe_info->fd_in, STDIN_FILENO);
		close(pipe_info->fd_in);
	}
	return (1);
}

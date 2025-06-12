/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:52:50 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/12 18:57:45 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

int	outfile_redirection(t_cmd *cmd)
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

int	infile_redirection(t_cmd *cmd, t_pipe_info *pipe_info)
{
	int	hd_fd[2];

	if (cmd->is_heredoc && cmd->heredoc_buffer)
	{
		if (!create_pipe(hd_fd))
			return (0);
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

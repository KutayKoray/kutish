/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:52:49 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/24 23:29:40 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void	infile_redirects(t_cmd *cmd, int *fd_in)
{
	int	hd_fd[2];

	if (cmd->is_heredoc && cmd->heredoc_buffer)
	{
		if (!create_pipe(hd_fd))
			exit(EXIT_GENERIC_ERR);
		write(hd_fd[1], cmd->heredoc_buffer, ft_strlen(cmd->heredoc_buffer));
		close(hd_fd[1]);
		dup2(hd_fd[0], STDIN_FILENO);
		close(hd_fd[0]);
	}
	else if (cmd->infile)
	{
		*fd_in = open(cmd->infile, O_RDONLY);
		if (*fd_in == -1)
			exit_with_error(EXIT_GENERIC_ERR, "kutish", 1);
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	else if (*fd_in != STDIN_FILENO)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
}

void	outfile_redirects(t_cmd *cmd, int *pipe_fd)
{
	size_t	i;
	int		fd;

	if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	i = 0;
	if (!cmd->outfiles || !*cmd->outfiles)
		return ;
	while (cmd->outfiles[i])
	{
		fd = open(cmd->outfiles[i], O_CREAT, 0644);
		if (fd == -1)
			exit_with_error(EXIT_GENERIC_ERR, "kutish", 1);
		close(fd);
		i++;
	}
	if (cmd->append)
		fd = open(cmd->outfiles[i - 1], O_WRONLY | O_APPEND);
	else
		fd = open(cmd->outfiles[i - 1], O_WRONLY | O_TRUNC);
	if (fd == -1)
		exit_with_error(EXIT_GENERIC_ERR, "kutish", 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

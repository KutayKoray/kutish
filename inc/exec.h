/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:52:57 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/28 18:43:36 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parser.h"
# include "env.h"

# define EXECUTION_SUCCESS 0
# define EXECUTION_FAILURE 1
# define SYNTAX_ERROR 2
# define EX_NOEXEC 126
# define EX_NOTFOUND 127

typedef struct	s_pipe_info
{
	int		pipe_fd[2];
	int		fd_in;
	int		original_stdin;
	int		original_stdout;
}	t_pipe_info;

// exec.c
void	execute_pipeline(t_cmd *cmd, t_env **env);

// exec_utils.c
int		create_pipe(int *fd);
int		is_builtin(char *cmd);
void	wait_for_pipeline(pid_t last_pid);

// exec_prep.c
char	*get_cmd_path(char *cmd, t_env *env);
char	**env2envp(t_env *env);

// exec_redir.c
int		infile_redirection(t_cmd *cmd, t_pipe_info *pipe_info);
int		outfile_redirection(t_cmd *cmd, t_pipe_info *pipe_info);

// exec_builtin.c
int		handle_builtin(t_cmd *cmd, t_env **env, t_pipe_info *pipe_info);
int		exec_builtin(t_cmd *cmd, t_env **env);

// utils/error.c
int		*exit_status(void);
void	exit_with_error(int status, const char *message, int is_exit);

void	exit_isadir(char *cmd, int is_exit);
void	exit_nocmd(char *cmd, int is_exit);

#endif
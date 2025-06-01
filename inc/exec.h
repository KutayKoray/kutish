/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:52:57 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/01 16:16:26 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parser.h"
# include "env.h"
# include "signals.h"

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
char	*get_cmd_path(t_cmd *cmd, t_env *env);
char	**env2envp(t_env *env);

// exec_redir.c
int		infile_redirection(t_cmd *cmd, t_pipe_info *pipe_info);
int		outfile_redirection(t_cmd *cmd);

// exec_builtin.c
void	handle_builtin(t_cmd *cmd, t_env **env);
int		handle_single_builtin(t_cmd *cmd, t_env **env, t_pipe_info *pipe_info);

// utils/exit_utils.c
int		*exit_status(void);
void	exit_with_error(int status, const char *message, int is_exit);
t_cmd	**get_cmd_head(t_cmd *cmd);
t_env	**get_env_head(t_env *env);
void	free_lists(void);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:52:57 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/25 14:29:28 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "env.h"

# define SHELL_NAME "kutish"

# define EXIT_SUCCESS 0
# define EXIT_GENERIC_ERR 1
# define EXIT_CANNOT_EXEC 126
# define EXIT_NO_CMD 127

// exec.c
void	execute_pipeline(t_cmd *cmd, t_env *env);

// exec_utils.c
int		*exit_status(void);
int		create_pipe(int *fd);
void	exit_with_error(int status, const char *message, int is_exit);

// exec_prep.c
char	*get_cmd_path(char *cmd, t_env *env);
char	**env2envp(t_env *env);

// exec_redir.c
void	infile_redirects(t_cmd *cmd, int *fd_in);
void	outfile_redirects(t_cmd *cmd, int *fd);

#endif
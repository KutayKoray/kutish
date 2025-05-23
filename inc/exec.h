/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:52:57 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/23 16:28:02 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "env.h"

// exec.c
int		*exit_status(void);

// exec_utils.c
char	*get_cmd_path(char *cmd, t_env *env);
char	**env2envp(t_env *env);

#endif
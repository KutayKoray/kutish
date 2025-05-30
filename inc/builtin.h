/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:52:58 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/30 17:48:33 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "utils.h"
# include "env.h"
# include "exec.h"

int	echo_builtin(char **argv);
int	export_builtin(char **argv, t_env **env);
int	unset_builtin(char **argv, t_env **env);
int	pwd_builtin(void);
int	env_builtin(t_env *env);
int	cd_builtin(char **argv, t_env **env);
int	exit_builtin(t_cmd *cmd, t_env *env);

#endif
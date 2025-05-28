/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:04:47 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/05/28 14:25:26 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils.h"
# include "parser.h"
# include "env.h"
# include "exec.h"
# include "builtin.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>

# define SHELL_NAME "kutish"

# define EXECUTION_SUCCESS 0
# define EXECUTION_FAILURE 1
# define SYNTAX_ERROR 2
# define EX_NOEXEC 126
# define EX_NOTFOUND 127

#endif
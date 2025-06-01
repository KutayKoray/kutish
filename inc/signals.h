/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:48:55 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/01 16:20:36 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"
void	exit_with_error(int status, const char *message, int is_exit);

void	set_signal_handler(int type);

void	prompt_handler(int signum);
void	sigquit_handler(int signum);
void	execute_handler(int signum);
void	heredoc_handler(int signum);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:01:38 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/01 16:11:21 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	prompt_handler(int signum)
{
	g_signal = signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit_with_error(signum + 128, NULL, 0);
}

void	sigquit_handler(int signum)
{
	g_signal = signum;
	printf("Quit (core dumped)\n");
	rl_replace_line("", 0);
	exit_with_error(signum + 128, NULL, 0);
}

void	execute_handler(int signum)
{
	g_signal = signum;
	printf("\n");
	exit_with_error(signum + 128, NULL, 0);
}

void	heredoc_handler(int signum)
{
	g_signal = signum;
	rl_replace_line("", 0);
	rl_done = 1;
	exit_with_error(signum + 128, NULL, 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:48:34 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/02 19:25:13 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static int	dummy_hook(void)
{
	return (0);
}

// type 0: prompt handler
// type 1: execution handler
// type 2: heredoc handler
void	set_signal_handler(int type)
{
	g_signal = 0;
	if (type == 0)
	{
		rl_event_hook = NULL;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, prompt_handler);
	}
	else if (type == 1)
	{
		rl_event_hook = NULL;
		signal(SIGQUIT, sigquit_handler);
		signal(SIGINT, execute_handler);
	}
	else if (type == 2)
	{
		rl_event_hook = dummy_hook;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, heredoc_handler);
	}
}

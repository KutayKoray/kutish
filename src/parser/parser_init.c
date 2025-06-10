/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:49 by kkoray            #+#    #+#             */
/*   Updated: 2025/06/10 17:22:10 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->outfiles = NULL;
	cmd->infile = NULL;
	cmd->heredoc_eof = NULL;
	cmd->heredoc_buffer = NULL;
	cmd->append = 0;
	cmd->is_heredoc = 0;
	cmd->heredoc_expand = 0;
	cmd->next = NULL;
	return (cmd);
}

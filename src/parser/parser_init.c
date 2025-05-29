/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:49 by kkoray            #+#    #+#             */
/*   Updated: 2025/05/29 19:15:06 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfiles = NULL;
	cmd->heredoc_eof = NULL;
	cmd->append = 0;
	cmd->is_heredoc = 0;
	cmd->heredoc_buffer = NULL;
	cmd->next = NULL;
	return (cmd);
}

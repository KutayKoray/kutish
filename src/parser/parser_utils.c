/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:49 by kkoray            #+#    #+#             */
/*   Updated: 2025/06/14 12:19:59 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

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

void	free_cmd_list(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		if (tmp->argv)
			free_str_arr(tmp->argv);
		if (tmp->outfiles)
			free_str_arr(tmp->outfiles);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->heredoc_eof)
			free_str_arr(tmp->heredoc_eof);
		if (tmp->heredoc_buffer)
			free(tmp->heredoc_buffer);
		free(tmp);
	}
}

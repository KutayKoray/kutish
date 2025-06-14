/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:37:12 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/14 12:28:15 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	print_cmd_fields(t_cmd *cmd)
{
	int	i;

	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			printf("  Arg[%d]: %s\n", i, cmd->argv[i]);
			i++;
		}
	}
	if (cmd->infile)
		printf("  Infile: %s\n", cmd->infile);
	if (cmd->outfiles)
	{
		i = 0;
		while (cmd->outfiles[i])
		{
			printf("  Outfile[%d]: %s\n", i, cmd->outfiles[i]);
			i++;
		}
	}
}

void	print_cmd_heredoc(t_cmd *cmd)
{
	int	k;

	if (cmd->heredoc_eof)
	{
		k = 0;
		while (cmd->heredoc_eof[k])
		{
			printf("  Heredoc[%d]: %s\n", k, cmd->heredoc_eof[k]);
			k++;
		}
	}
	printf("  Append: %d\n", cmd->append);
	printf("  Is Heredoc: %d\n", cmd->is_heredoc);
	if (cmd->is_heredoc)
		printf("  Heredoc Expand: %d\n", cmd->heredoc_expand);
	if (cmd->heredoc_buffer)
		printf("  Heredoc Buffer: %s\n", cmd->heredoc_buffer);
}

void	print_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		cmd_index;

	tmp = cmd;
	cmd_index = 0;
	while (tmp)
	{
		printf("\nCommand #%d:\n", cmd_index);
		print_cmd_fields(tmp);
		print_cmd_heredoc(tmp);
		tmp = tmp->next;
		cmd_index++;
	}
}

void	debug_print_cmd(t_token *tokens, char *msg)
{
	int		i;

	printf("\n%s\n", msg);
	i = 0;
	while (tokens)
	{
		printf("Token #%d:\n", i);
		printf("  Value   : %s\n", tokens->value);
		printf("  Type    : %d\n", tokens->type);
		printf("  Joined  : %d\n", tokens->joined);
		printf("  Trimmed : %d\n", tokens->trimmed);
		printf("  Expanded: %d\n", tokens->expanded);
		tokens = tokens->next;
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:48:10 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/16 16:24:59 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

void	add_heredoc(char ***heredoc_eof, const char *value)
{
	char	**new;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (*heredoc_eof)
		while ((*heredoc_eof)[len])
			len++;
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return ;
	while (i < len)
	{
		new[i] = (*heredoc_eof)[i];
		i++;
	}
	new[len] = ft_strdup(value);
	new[len + 1] = NULL;
	free(*heredoc_eof);
	*heredoc_eof = new;
}

static char	*read_heredoc_input(const char *eof)
{
	char	*line;
	char	*buffer;
	char	*tmp_buff;
	char	*tmp;

	buffer = ft_calloc(1, 1);
	if (!buffer)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, eof) || g_signal)
		{
			free(line);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		tmp_buff = ft_strjoin(buffer, tmp);
		free(buffer);
		free(tmp);
		free(line);
		buffer = tmp_buff;
	}
	return (buffer);
}

char	*get_heredoc(t_cmd *cmd)
{
	size_t	i;
	size_t	count;
	char	*last_input;

	count = 0;
	i = 0;
	last_input = NULL;
	while (cmd->heredoc_eof[count])
		count++;
	while (i < count)
	{
		free(last_input);
		last_input = read_heredoc_input(cmd->heredoc_eof[i]);
		if (!last_input)
			return ("\006");
		if (g_signal)
		{
			free(last_input);
			return (NULL);
		}
		i++;
	}
	return (last_input);
}

void	assign_heredoc_buffers(t_cmd *cmds, t_env *env)
{
	t_cmd	*cur;
	char	*raw;

	set_signal_handler(2);
	cur = cmds;
	while (cur)
	{
		if (cur->is_heredoc)
		{
			raw = get_heredoc(cur);
			if (!raw || !ft_strncmp(raw, "\006", 1))
				return ;
			if (cur->heredoc_expand)
			{
				cur->heredoc_buffer = expand_input(raw, NULL, env);
				free(raw);
			}
			else
				cur->heredoc_buffer = raw;
		}
		cur = cur->next;
	}
	set_signal_handler(0);
}

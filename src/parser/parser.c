/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:52 by kkoray            #+#    #+#             */
/*   Updated: 2025/06/14 12:19:49 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static void	add_outfile(char ***outfiles, char *value)
{
	int		len;
	int		i;
	char	**new;

	len = 0;
	i = 0;
	if (*outfiles)
		while ((*outfiles)[len])
			len++;
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return ;
	while (i < len)
	{
		new[i] = (*outfiles)[i];
		i++;
	}
	new[len] = ft_strdup(value);
	new[len + 1] = NULL;
	free(*outfiles);
	*outfiles = new;
}

static void	add_arg(char ***argv, char *value)
{
	int		len;
	int		i;
	char	**new;

	len = 0;
	i = 0;
	if (*argv)
		while ((*argv)[len])
			len++;
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
	{
		free(*argv);
		return ;
	}
	while (i < len)
	{
		new[i] = (*argv)[i];
		i++;
	}
	new[len] = ft_strdup(value);
	new[len + 1] = NULL;
	free(*argv);
	*argv = new;
}

static void	handle_word_and_redir(t_token **tokens, t_cmd *cur)
{
	if ((*tokens)->type == T_WORD && *(*tokens)->value)
		add_arg(&cur->argv, (*tokens)->value);
	else if ((*tokens)->type == T_REDIN && (*tokens)->next)
	{
		cur->infile = ft_strdup((*tokens)->next->value);
		*tokens = (*tokens)->next;
	}
	else if ((*tokens)->type == T_REDOUT && (*tokens)->next)
	{
		add_outfile(&cur->outfiles, (*tokens)->next->value);
		cur->append = 0;
		*tokens = (*tokens)->next;
	}
	else if ((*tokens)->type == T_APPEND && (*tokens)->next)
	{
		add_outfile(&cur->outfiles, (*tokens)->next->value);
		cur->append = 1;
		*tokens = (*tokens)->next;
	}
}

static t_cmd	*handle_heredoc_and_pipe(t_token **tokens, t_cmd *cur)
{
	if ((*tokens)->type == T_HEREDOC && (*tokens)->next)
	{
		add_heredoc(&cur->heredoc_eof, (*tokens)->next->value);
		cur->is_heredoc = 1;
		cur->heredoc_expand = !(*tokens)->next->trimmed;
		*tokens = (*tokens)->next;
	}
	else if ((*tokens)->type == T_PIPE)
	{
		cur->next = create_cmd();
		cur = cur->next;
	}
	return (cur);
}

t_cmd	*parse_tokens(t_token *tokens, t_env *env)
{
	t_cmd	*head;
	t_cmd	*cur;

	cur = create_cmd();
	if (!cur)
		return (NULL);
	head = cur;
	while (tokens)
	{
		handle_word_and_redir(&tokens, cur);
		cur = handle_heredoc_and_pipe(&tokens, cur);
		tokens = tokens->next;
	}
	assign_heredoc_buffers(head, env);
	return (head);
}

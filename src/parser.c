/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoray <kkoray@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:32:52 by kkoray            #+#    #+#             */
/*   Updated: 2025/04/26 12:32:53 by kkoray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if ((*tokens)->type == T_WORD)
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
		cur->heredoc_eof = ft_strdup((*tokens)->next->value);
		cur->is_heredoc = 1;
		*tokens = (*tokens)->next;
	}
	else if ((*tokens)->type == T_PIPE)
	{
		cur->next = create_cmd();
		cur = cur->next;
	}
	return (cur);
}

t_cmd	*parse_tokens(t_token *tokens)
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
	return (head);
}

void	print_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		j;

	tmp = cmd;
	printf("--------------------------------\n");
	while (tmp)
	{
		printf("Command:\n");
		if (tmp->argv)
		{
			for (int i = 0; tmp->argv[i]; i++)
				printf("Arg[%d]: %s\n", i, tmp->argv[i]);
		}
		if (tmp->infile)
			printf("Infile: %s\n", tmp->infile);
		if (tmp->outfiles)
		{
			j = 0;
			while (tmp->outfiles[j])
			{
				printf("Outfile[%d]: %s\n", j, tmp->outfiles[j]);
				j++;
			}
		}
		if (tmp->heredoc_eof)
			printf("Heredoc EOF: %s\n", tmp->heredoc_eof);
		if (tmp->append)
			printf("Append: %d\n", tmp->append);
		if (tmp->is_heredoc)
			printf("Is Heredoc: %d\n", tmp->is_heredoc);
		if (tmp->next)
			printf("Next Command:\n");
		else
			printf("End of Command List\n");
		tmp = tmp->next;
	}
	printf("--------------------------------\n");
}

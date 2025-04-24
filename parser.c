#include "minishell.h"

static t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->heredoc_eof = NULL;
	cmd->append = 0;
	cmd->is_heredoc = 0;
	cmd->next = NULL;
	return (cmd);
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

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head = NULL;
	t_cmd	*cur = create_cmd();

	if (!cur)
		return (NULL);
	head = cur;

	while (tokens)
	{
		if (tokens->type == T_WORD)
		{
			add_arg(&cur->argv, tokens->value);
		}
		else if (tokens->type == T_REDIN && tokens->next)
		{
			cur->infile = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == T_REDOUT && tokens->next)
		{
			cur->outfile = ft_strdup(tokens->next->value);
			cur->append = 0;
			tokens = tokens->next;
		}
		else if (tokens->type == T_APPEND && tokens->next)
		{
			cur->outfile = ft_strdup(tokens->next->value);
			cur->append = 1;
			tokens = tokens->next;
		}
		else if (tokens->type == T_HEREDOC && tokens->next)
		{
			cur->heredoc_eof = ft_strdup(tokens->next->value);
			cur->is_heredoc = 1;
			tokens = tokens->next;
		}
		else if (tokens->type == T_PIPE)
		{
			cur->next = create_cmd();
			cur = cur->next;
			if (!cur)
				return (head);
		}
		tokens = tokens->next;
	}
	return (head);
}

void print_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp = cmd;

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
		if (tmp->outfile)
			printf("Outfile: %s\n", tmp->outfile);
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

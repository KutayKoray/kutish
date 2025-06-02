/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:25:36 by ebabaogl          #+#    #+#             */
/*   Updated: 2025/06/02 19:25:38 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prettify_buffer(char *buffer)
{
	char	*tmp;
	int		i;

	tmp = malloc(sizeof(char) * (ft_strlen(buffer) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			tmp[i] = '\\';
		else
			tmp[i] = buffer[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void print_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i, j;

	tmp = cmd;
	printf("\nCommand List:\n");
	printf("╭───────────────────────────────┬────────────────────────────────────────────╮\n");
	printf("│ %-29s │ %-42s │\n", "Field", "Value");
	printf("├───────────────────────────────┼────────────────────────────────────────────┤\n");
	while (tmp)
	{
		printf("│ %-29s │ %-42s │\n", "Command", "(argv list below)");
		if (tmp->argv)
		{
			for (i = 0; tmp->argv[i]; i++)
				printf("│   Arg[%d]                      │ %-42s │\n", i, tmp->argv[i]);
		}
		if (tmp->infile)
			printf("│ Infile                        │ %-42s │\n", tmp->infile);
		if (tmp->outfiles)
		{
			for (j = 0; tmp->outfiles[j]; j++)
				printf("│ Outfile[%d]                    │ %-42s │\n", j, tmp->outfiles[j]);
		}
		if (tmp->heredoc_eof)
		{
			int k = 0;
			while (tmp->heredoc_eof[k])
			{
				printf("│ Heredoc[%d]                    │ %-42s │\n", k, tmp->heredoc_eof[k]);
				k++;
			}
		}
		printf("│ Append                        │ %-42d │\n", tmp->append);
		printf("│ Is Heredoc                    │ %-42d │\n", tmp->is_heredoc);
		if (tmp->is_heredoc)
			printf("│ Heredoc Expand                │ %-42d │\n", tmp->heredoc_expand);
		if (tmp->heredoc_buffer)
			printf("│ Heredoc Buffer                │ %-42s │\n", prettify_buffer(tmp->heredoc_buffer));
		if (tmp->next)
		{
			printf("├───────────────────────────────┼────────────────────────────────────────────┤\n");
			printf("│ %-29s │ %-42s │\n", "Next Command", "(linked)");
			printf("├───────────────────────────────┼────────────────────────────────────────────┤\n");
		}
		else
			printf("╰───────────────────────────────┴────────────────────────────────────────────╯\n");
		tmp = tmp->next;
	}
}

void    debug_print_cmd(t_token *tokens, char *msg)
{
	t_token *tmp;

	tmp = tokens;
	printf("\n%s\n", msg);
	printf("╭───────────────────────────────┬───────────┬──────────┬───────────╮\n");
	printf("│ %-29s │ %-9s │ %-8s │ %-9s │\n", "Token", "Type", "Joined", "Trimmed");
	printf("├───────────────────────────────┼───────────┼──────────┼───────────┤\n");
	while (tmp)
	{
		printf("│ %-29s │ %-9d │ %-8d │ %-9d │\n",
			tmp->value, tmp->type, tmp->joined, tmp->trimmed);
		tmp = tmp->next;
	}
	printf("╰───────────────────────────────┴───────────┴──────────┴───────────╯\n");
}
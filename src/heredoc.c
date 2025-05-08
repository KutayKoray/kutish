#include "minishell.h"

void	add_heredoc(char ***heredoc_eof, const char *value)
{
	int		len = 0;
	char	**new;
	int		i = 0;

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
	char	*tmp;

	buffer = ft_calloc(1, 1);
	if (!buffer)
		return NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, eof))
		{
			free(line);
			break;
		}
		tmp = ft_strjoin(line, "\n");
		buffer = strappend_str(buffer, tmp);
		free(tmp);
		free(line);
	}
	return (buffer);
}

static void	discard_heredoc_inputs(char **heredocs, int count)
{
	int	i = 0;

	while (i < count)
	{
		read_heredoc_input(heredocs[i]);
		i++;
	}
}

char	*get_heredoc(t_cmd *cmd)
{
	int		count;
	char	*last_input;
	char	*last_new_line;

	if (!cmd || !cmd->heredoc_eof)
		return (NULL);
	count = 0;
	while (cmd->heredoc_eof[count])
		count++;
	if (count > 1)
		discard_heredoc_inputs(cmd->heredoc_eof, count - 1);
	last_input = read_heredoc_input(cmd->heredoc_eof[count - 1]);
	last_new_line = ft_strrchr(last_input, '\n');
	if (!last_new_line)
	{
		free(last_input);
		return (NULL);
	}
	*last_new_line = '\0';
	return (last_input);
}

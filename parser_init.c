#include "minishell.h"

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
	cmd->next = NULL;
	return (cmd);
}

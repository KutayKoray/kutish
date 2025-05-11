#include "minishell.h"

static int	should_split_echo_str(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == ' ')
		i++;
	if (ft_strncmp(&str[i], "echo", 4) != 0)
		return (0);
	i += 4;
	if (str[i] != ' ' && str[i] != '\0')
		return (0);
	return (1);
}

void	handle_echo_token_split(t_token **tokens)
{
	t_token	*cur;
	t_token	*second;
	char	*rest;
	int		i;

	cur = *tokens;
	if (!cur || cur->next)
		return ;
	if (cur->type != T_WORD || cur->trimmed)
		return ;
	if (!should_split_echo_str(cur->value))
		return ;
	i = 0;
	while (cur->value[i] == ' ')
		i++;
	i += 4;
	while (cur->value[i] == ' ')
		i++;
	rest = ft_strdup(&cur->value[i]);
	second = create_token(rest, T_WORD, 0, 0);
	free(rest);
	free(cur->value);
	cur->value = ft_strdup("echo");
	cur->next = second;
}


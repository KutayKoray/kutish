int	operator_length(const char *s)
{
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		return (2);
	return (1);
}

int	skip_space(const char *input, int i, int *prev_was_space)
{
	if (input[i] == ' ')
	{
		*prev_was_space = 1;
		return (i + 1);
	}
	return (i);
}

int	is_operator_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	read_quoted(const char *str, int start, char quote)
{
	int	i;

	i = start + 1;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

int	read_plain(const char *str, int start)
{
	int	i;

	i = start;
	while (str[i] && str[i] != '\'' && str[i] != '"' && str[i] != ' '
		&& !is_operator_char(str[i]))
		i++;
	return (i);
}

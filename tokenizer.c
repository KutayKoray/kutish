#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

void	ft_add_token(t_token **tokens, t_token *new_token)
{
	t_token	*temp;

	if (!new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	temp = *tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
}

t_token_type	ft_get_special_token_type(char c, char next)
{
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '<' && next == '<')
		return (TOKEN_HEREDOC);
	if (c == '>' && next == '>')
		return (TOKEN_REDIRECT_APPEND);
	if (c == '<')
		return (TOKEN_REDIRECT_IN);
	if (c == '>')
		return (TOKEN_REDIRECT_OUT);
	return (TOKEN_WORD);
}

void	ft_tokenize(char *input, t_token **tokens)
{
	int				i;
	t_token_type	type;
	int				len;
	char			*substr;
	int				start;
	char			quote;

	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		if (ft_strchr("|<>", input[i]))
		{
			type = ft_get_special_token_type(input[i], input[i + 1] ? input[i
					+ 1] : '\0');
			len = (type == TOKEN_HEREDOC
					|| type == TOKEN_REDIRECT_APPEND) ? 2 : 1;
			substr = ft_strndup(&input[i], len);
			if (!substr)
			{
				perror("malloc error");
				exit(EXIT_FAILURE);
			}
			ft_add_token(tokens, ft_new_token(substr, type));
			i += len;
		}
		else
		{
			start = i;
			if (input[i] == '"' || input[i] == '\'')
			{
				quote = input[i++];
				while (input[i] && input[i] != quote)
					i++;
				if (input[i] == quote)
					i++;
			}
			else
			{
				while (input[i] && !ft_strchr(" |<>", input[i]))
					i++;
			}
			substr = ft_strndup(&input[start], i - start);
			if (!substr)
			{
				perror("malloc error");
				exit(EXIT_FAILURE);
			}
			ft_add_token(tokens, ft_new_token(substr, TOKEN_WORD));
		}
	}
}

void	ft_print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: [%s] Type: [(%u)]\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

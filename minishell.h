#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_DQUOTE,
	TOKEN_SQUOTE,
	TOKEN_DOLLAR,
	TOKEN_EOF
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

t_token				*lexer(const char *input);
void				print_tokens(t_token *token);
void				expand_variables(t_token *tokens);

#endif
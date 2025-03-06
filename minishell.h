#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>

typedef enum
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
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

typedef struct s_ast
{
	char			*cmd;
	char			**args;
	char			*redirect_in;
	char			*redirect_out;
	int				append;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

t_token				*expander(t_token *tokens);

void				ft_tokenize(char *input, t_token **tokens);
void				ft_print_tokens(t_token *tokens);

char				*ft_strndup(const char *s, int n);
char				*ft_strjoin_free(char *s1, const char *s2, int free_s1);
char				*handle_variable(const char *str, size_t *i);

int					ft_strcmp(const char *s1, const char *s2);

#endif
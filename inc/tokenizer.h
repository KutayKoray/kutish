#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "minishell.h"
#include "utils.h"

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIN,
	T_REDOUT,
	T_APPEND,
	T_HEREDOC
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				joined;
	int				trimmed;
	struct s_token	*next;
}					t_token;

typedef struct s_token_ctx
{
	t_token			**head;
	int				joined;
}					t_token_ctx;

t_token	*tokenize(const char *input);
void			free_token_list(t_token *tokens);
int				operator_length(const char *s);
int				skip_space(const char *input, int i, int *prev_was_space);
int				is_operator_char(char c);
t_token			*create_token(const char *value, t_token_type type, int joined, int trimmed);
t_token_type	get_operator_type(const char *s);
void			add_token(t_token **head, char *value, t_token_type type, int joined);
int				read_word(const char *str, int start);

# endif
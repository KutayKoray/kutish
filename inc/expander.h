#ifndef EXPANDER_H
#define EXPANDER_H

#include "env.h"
#include "minishell.h"
#include "tokenizer.h"

typedef struct s_expand_ctx
{
	char	*result;
	int		in_single_quote;
	int		in_double_quote;
	char	first_quote;
	t_env	*env;
}	t_expand_ctx;

void	expand_token_list(t_token *tokens, t_env *env);
char	*char_to_str(char c);
size_t	get_env_key_len(const char *str, size_t *i);

#endif
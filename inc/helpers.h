#ifndef HELPERS_H
#define HELPERS_H

#include "tokenizer.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"

int     quote_checker(const char *input);
void    trim_token_quotes(t_token *tokens);
void    print_cmd_list(t_cmd *cmd);
void    debug_print_cmd(t_token *tokens, char *msg);
void	split_first_token_head_tail(t_token **tokens);
t_token	*create_token(const char *value, t_token_type type, int joined, int trimmed);
t_token	*create_token_list_from_split(char **parts, t_token *cur);

#endif
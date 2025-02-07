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

typedef struct s_ast {
    char *cmd;            // Komut (örneğin: "ls", "grep")
    char **args;          // Argümanlar (örneğin: ["grep", "txt"])
    char *redirect_in;    // "<" veya "<<" yönlendirmesi (örneğin: "input.txt")
    char *redirect_out;   // ">" veya ">>" yönlendirmesi (örneğin: "output.txt")
    int append;           // ">>" olup olmadığını belirler (1 = append, 0 = overwrite)
    struct s_ast *left;   // Boru hattındaki önceki komut (örn: "ls")
    struct s_ast *right;  // Boru hattındaki sonraki komut (örn: "grep txt")
} t_ast;

t_ast				*parse_tokens(t_token *tokens);
t_token				*lexer(const char *input);
void				print_tokens(t_token *token);
void				expand_variables(t_token *tokens);
void				print_ast(t_ast *node);
t_ast				*parse_tokens(t_token *tokens);
void				run_ast(t_ast *ast);

#endif
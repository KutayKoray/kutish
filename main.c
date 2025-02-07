#include "minishell.h"
#include <stdio.h>

int main(void) {
    char *input = "ls -l | grep txt | wc -l > output.txt";
    t_token *tokens = lexer(input);
    print_tokens(tokens);

    expand_variables(tokens);

    printf("\nSonrası:\n");
    print_tokens(tokens);

    printf("\nAST:\n");
    t_ast *root = parse_tokens(tokens);
    print_ast(root);

    printf("\nRunning AST...\n");
    run_ast(root);

    return 0;
}



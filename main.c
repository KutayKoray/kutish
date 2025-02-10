#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROMPT "minishell$ "

int main(void) {
    char *input = NULL;
    size_t len = 0;
    
    while (1) 
    {
        printf(PROMPT);
        fflush(stdout);

        ssize_t read = getline(&input, &len, stdin);
        if (read == -1) {
            printf("\nÇıkılıyor...\n");
            break;
        }

        if (input[read - 1] == '\n') {
            input[read - 1] = '\0';
        }

        if (strcmp(input, "exit") == 0) {
            printf("Çıkılıyor...\n");
            break;
        }

        t_token *tokens = lexer(input);
        if (!tokens) continue;

        //print_tokens(tokens); for debugging

        expand_variables(tokens);

        t_ast *root = parse_tokens(tokens);
        if (!root) continue;

        // print_ast(root, 0); for debugging

        run_ast(root);
    }

    free(input);
    return 0;
}

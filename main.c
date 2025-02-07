#include "minishell.h"
#include <stdio.h>

int main() {
    char *input = "echo $HOME $USER $?";
    t_token *tokens = lexer(input);
    print_tokens(tokens);
    
    expand_variables(tokens); // Expander'ı çalıştır

    printf("\nSonrası:\n\n");

    print_tokens(tokens); // Expander sonrası çıktıyı gör
    return 0;
}


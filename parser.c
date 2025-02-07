#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_ast *parse_tokens(t_token *tokens) {
    t_ast *root = NULL;
    t_ast *current_node = NULL;
    t_ast *last_cmd = NULL;
    t_token *current = tokens;


    while (current) {

        if (current->type == TOKEN_PIPE) { 

            t_ast *pipe_node = malloc(sizeof(t_ast));
            memset(pipe_node, 0, sizeof(t_ast));

            pipe_node->left = root;  // Önceki kökü sola bağla

            root = pipe_node;  // Yeni pipe düğümünü kök yap
            current_node = NULL;  // Yeni komut için düğüm başlat
        } 
        else if (current->type == TOKEN_REDIRECT_OUT) { 

            if (last_cmd) {
                last_cmd->redirect_out = strdup(current->next->value); 
                current = current->next;  // Dosya adını atla
            }
        } 
        else { 

            t_ast *node = malloc(sizeof(t_ast));
            memset(node, 0, sizeof(t_ast));
            node->cmd = strdup(current->value);

            if (!root) { 
                root = node;
            } 
            else if (!current_node) { 
                root->right = node;  // PIPE düğümünün sağına bağla
            } 
            else {
                current_node->right = node;
            }

            current_node = node;
            last_cmd = node;
        }
        current = current->next;
    }

    return root;
}




void print_ast(t_ast *node) {
    if (!node) return;

    if (node->left) { 
        printf("[PIPE]\n");
        print_ast(node->left);
    }

    if (node->cmd) {
        printf("[CMD]: %s", node->cmd);
        if (node->redirect_out)
            printf("\n   [>]: %s", node->redirect_out);
        if (node->redirect_in)
            printf("\n   [<]: %s", node->redirect_in);
        printf("\n");
    }

    if (node->right)
        print_ast(node->right);
}


#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_ARGS 10  // Her komut için maksimum argüman sayısı

t_ast *parse_tokens(t_token *tokens) {
    t_ast *root = NULL;         // Tüm AST’nin kökü (pipeline düğümleri de burada yer alacak)
    t_ast *current_cmd = NULL;  // Şu anda oluşturmakta olduğumuz komut düğümü
    int arg_index = 0;          // Mevcut komut düğümüne eklenen argüman sayısı
    t_token *current = tokens;

    while (current) {
        if (current->type == TOKEN_PIPE) {
            // PIPE token’ü geldiğinde, mevcut komut düğümünü bitirip, pipeline düğümü oluşturun.
            if (current_cmd) {
                // Eğer henüz bir AST kökü yoksa, current_cmd doğrudan kök olur;
                // aksi halde, mevcut kökün (veya pipeline zincirinin) en sağa current_cmd’yi ekleyin.
                if (!root) {
                    root = current_cmd;
                } else {
                    t_ast *temp = root;
                    while (temp->right)
                        temp = temp->right;
                    temp->right = current_cmd;
                }
                current_cmd = NULL;
                arg_index = 0;
            }
            // Şimdi yeni bir PIPE düğümü oluşturun.
            t_ast *pipe_node = malloc(sizeof(t_ast));
            if (!pipe_node) {
                perror("malloc");
                exit(1);
            }
            memset(pipe_node, 0, sizeof(t_ast));
            // PIPE düğümünde cmd, args, redirection alanları kullanılmaz (NULL bırakılır).
            // PIPE düğümü, solunda daha önceki komut zincirini barındırır.
            if (!root) {
                // Eğer henüz kök yoksa, hata durumunu (ya da boş komut zincirini) kontrol edebilirsiniz.
                pipe_node->left = NULL;
            } else {
                pipe_node->left = root;
            }
            // Bu yeni PIPE düğümünü yeni kök olarak ayarlıyoruz.
            root = pipe_node;
            // Sonraki komut için current_cmd sıfırlanır.
            current_cmd = NULL;
            arg_index = 0;
        }
        else if (current->type == TOKEN_REDIRECT_OUT) {
            if (current_cmd && current->next) {
                current_cmd->redirect_out = strdup(current->next->value);
                current_cmd->append = 0;  // ">" olduğunda append 0
                current = current->next;
            }
        }
        else if (current->type == TOKEN_REDIRECT_APPEND) {  // ">>" için ayrı case
            if (current_cmd && current->next) {
                current_cmd->redirect_out = strdup(current->next->value);
                current_cmd->append = 1;  // ">>" olduğunda append 1
                current = current->next;
            }
        }
        else if (current->type == TOKEN_REDIRECT_IN) {
            // Giriş yönlendirmesi
            if (current_cmd && current->next) {
                current_cmd->redirect_in = strdup(current->next->value);
                current = current->next;
            }
        }
        else {
            // TOKEN_WORD veya diğer komut/argüman token’leri
            if (current_cmd == NULL) {
                // Yeni bir komut düğümü oluşturun.
                current_cmd = malloc(sizeof(t_ast));
                if (!current_cmd) {
                    perror("malloc");
                    exit(1);
                }
                memset(current_cmd, 0, sizeof(t_ast));
                // Argümanlar için sabit boyutlu dizi ayırın.
                current_cmd->args = malloc(sizeof(char *) * MAX_ARGS);
                if (!current_cmd->args) {
                    perror("malloc");
                    exit(1);
                }
                for (int i = 0; i < MAX_ARGS; i++)
                    current_cmd->args[i] = NULL;
                arg_index = 0;
                // İlk token komut adı olarak kaydedilir.
                current_cmd->cmd = strdup(current->value);
                current_cmd->args[arg_index++] = strdup(current->value);
            } else {
                // Mevcut komut düğümüne argüman ekleyin.
                if (arg_index < MAX_ARGS - 1) {
                    current_cmd->args[arg_index++] = strdup(current->value);
                }
            }
        }
        current = current->next;
    }
    // Döngü sonunda, eğer bitmemiş bir komut düğümü varsa, AST’ye ekleyin.
    if (current_cmd) {
        if (!root) {
            root = current_cmd;
        } else {
            t_ast *temp = root;
            while (temp->right)
                temp = temp->right;
            temp->right = current_cmd;
        }
    }
    return root;
}

void print_ast(t_ast *node, int depth) {
    if (!node)
        return;
    
    // Derinliğe göre boşluklar (indentation)
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    // Eğer düğümde komut yoksa, bunu bir PIPE düğümü olarak kabul ediyoruz.
    if (node->cmd == NULL) {
        printf("[PIPE]\n");
    } else {
        // Komut düğümü: Komut adını yazdırıyoruz.
        printf("[CMD]: %s", node->cmd);
        
        // Argümanlar varsa yazdır.
        if (node->args) {
            for (int i = 0; node->args[i] != NULL; i++) {
                printf(" %s", node->args[i]);
            }
        }
        
        // Giriş yönlendirmesi varsa.
        if (node->redirect_in)
            printf(" [<]: %s", node->redirect_in);
        
        // Çıkış yönlendirmesi varsa.
        if (node->redirect_out)
            printf(" [>]: %s (%s)", node->redirect_out, node->append ? "APPEND" : "OVERWRITE");
        
        printf("\n");
    }
    
    // Sol alt ağaç (pipe’ın sol tarafı)
    if (node->left)
        print_ast(node->left, depth + 1);
    
    // Sağ alt ağaç (pipe’ın sağ tarafı)
    if (node->right)
        print_ast(node->right, depth + 1);
}


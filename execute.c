#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

// AST ağacında, cmd alanı dolu düğümlerin sayısını in-order dolaşarak sayar.
int count_inorder(t_ast *node) {
    if (!node)
        return 0;
    int count = count_inorder(node->left);
    if (node->cmd)
        count++;
    count += count_inorder(node->right);
    return count;
}

// AST ağacında, in-order dolaşım yaparak cmd alanı dolu düğümleri array'e ekler.
void collect_commands_inorder(t_ast *node, t_ast **array, int *index) {
    if (!node)
        return;
    collect_commands_inorder(node->left, array, index);
    if (node->cmd)
        array[(*index)++] = node;
    collect_commands_inorder(node->right, array, index);
}

void execute_pipeline_chain(t_ast *ast) {
    // In-order dolaşarak geçerli komut düğümlerinin sayısını alalım.
    int cmd_count = count_inorder(ast);
    if (cmd_count == 0)
        return;
    
    // Komut düğümlerini in-order dolaşım ile toplayalım.
    t_ast **commands = malloc(sizeof(t_ast *) * cmd_count);
    if (!commands) {
        perror("malloc");
        exit(1);
    }
    int index = 0;
    collect_commands_inorder(ast, commands, &index);
    
    // Pipeline için (cmd_count - 1) adet pipe gerekir.
    int num_pipes = cmd_count - 1;
    int pipefds[2 * num_pipes];
    for (int i = 0; i < num_pipes; i++) {
        if (pipe(pipefds + i * 2) < 0) {
            perror("pipe");
            exit(1);
        }
    }
    
    // Her komut için fork yapalım.
    for (int i = 0; i < cmd_count; i++) {
        pid_t pid = fork();
        if (pid == 0) {  // Çocuk süreç
            // İlk komut değilse, önceki pipe'ın okuma ucunu STDIN'e yönlendir.
            if (i != 0) {
                if (dup2(pipefds[(i - 1) * 2], STDIN_FILENO) < 0) {
                    perror("dup2 input");
                    exit(1);
                }
            }
            // Son komut değilse, mevcut pipe'ın yazma ucunu STDOUT'a yönlendir.
            if (i != cmd_count - 1) {
                if (dup2(pipefds[i * 2 + 1], STDOUT_FILENO) < 0) {
                    perror("dup2 output");
                    exit(1);
                }
            }
            // Tüm pipe dosya tanımlayıcılarını kapatalım.
            for (int j = 0; j < 2 * num_pipes; j++) {
                close(pipefds[j]);
            }
            // Redirection varsa (bu komuta ait) uygulayalım.
            t_ast *cmd = commands[i];
            if (cmd->redirect_in) {
                int fd_in = open(cmd->redirect_in, O_RDONLY);
                if (fd_in == -1) {
                    perror("open input file");
                    exit(1);
                }
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }
            if (cmd->redirect_out) {
                int fd_out;
                if (cmd->append)
                    fd_out = open(cmd->redirect_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
                else
                    fd_out = open(cmd->redirect_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd_out == -1) {
                    perror("open output file");
                    exit(1);
                }
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            }
            // Komutu çalıştır.
            execvp(cmd->args[0], cmd->args);
            perror("execvp failed");
            exit(1);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
    }
    
    // Parent: Tüm pipe dosya tanımlayıcılarını kapat.
    for (int j = 0; j < 2 * num_pipes; j++) {
        close(pipefds[j]);
    }
    // Tüm çocuk süreçlerin tamamlanmasını bekleyelim.
    for (int i = 0; i < cmd_count; i++) {
        wait(NULL);
    }
    free(commands);
}

void execute_command(t_ast *ast) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }
    if (pid == 0) {  // Çocuk süreç
        if (ast->redirect_in) {
            int fd_in = open(ast->redirect_in, O_RDONLY);
            if (fd_in == -1) {
                perror("open input file");
                exit(1);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        if (ast->redirect_out) {
            int fd_out;
            if (ast->append)
                fd_out = open(ast->redirect_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
            else
                fd_out = open(ast->redirect_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out == -1) {
                perror("open output file");
                exit(1);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        execvp(ast->args[0], ast->args);
        perror("execvp");
        exit(1);
    } else {
        waitpid(pid, NULL, 0);
    }
}

void run_ast(t_ast *ast) {
    // Eğer pipeline zincirinde birden fazla komut varsa:
    if (ast && (ast->left || ast->right)) {
        execute_pipeline_chain(ast);
    } else if (ast) {
        execute_command(ast);
    }
}


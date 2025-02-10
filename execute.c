#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

// AST ağacında cmd içeren düğümleri sayar.
int count_inorder(t_ast *node) {
    if (!node)
        return 0;
    return count_inorder(node->left) + (node->cmd ? 1 : 0) + count_inorder(node->right);
}

// AST ağacındaki komut düğümlerini toplar.
void collect_commands_inorder(t_ast *node, t_ast **array, int *index) {
    if (!node)
        return;
    collect_commands_inorder(node->left, array, index);
    if (node->cmd)
        array[(*index)++] = node;
    collect_commands_inorder(node->right, array, index);
}

void execute_pipeline_chain(t_ast *ast) {
    int cmd_count = count_inorder(ast);
    if (cmd_count == 0)
        return;
    
    t_ast **commands = malloc(sizeof(t_ast *) * cmd_count);
    if (!commands) {
        perror("malloc");
        exit(1);
    }
    int index = 0;
    collect_commands_inorder(ast, commands, &index);
    
    int num_pipes = cmd_count - 1;
    int pipefds[2 * num_pipes];
    for (int i = 0; i < num_pipes; i++) {
        if (pipe(pipefds + i * 2) < 0) {
            perror("pipe");
            exit(1);
        }
    }
    
    for (int i = 0; i < cmd_count; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            if (i != 0) {
                dup2(pipefds[(i - 1) * 2], STDIN_FILENO);
            }
            if (i != cmd_count - 1) {
                dup2(pipefds[i * 2 + 1], STDOUT_FILENO);
            }
            for (int j = 0; j < 2 * num_pipes; j++) {
                close(pipefds[j]);
            }
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
                int fd_out = open(cmd->redirect_out, O_WRONLY | O_CREAT | (cmd->append ? O_APPEND : O_TRUNC), 0644);
                if (fd_out == -1) {
                    perror("open output file");
                    exit(1);
                }
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            }
            execvp(cmd->args[0], cmd->args);
            perror("execvp failed");
            exit(1);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
    }
    
    for (int j = 0; j < 2 * num_pipes; j++) {
        close(pipefds[j]);
    }
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
    if (pid == 0) {
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
            int fd_out = open(ast->redirect_out, O_WRONLY | O_CREAT | (ast->append ? O_APPEND : O_TRUNC), 0644);
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
    if (ast && (ast->left || ast->right)) {
        execute_pipeline_chain(ast);
    } else if (ast) {
        execute_command(ast);
    }
}

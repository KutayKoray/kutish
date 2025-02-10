#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "minishell.h"

t_token *new_token(const char *value, t_token_type type) {
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = strdup(value);
    token->type = type;
    token->next = NULL;
    return token;
}

t_token *lexer(const char *input) {
    t_token *head = NULL, *tail = NULL;
    int i = 0, start;

    while (input[i]) {
        while (isspace(input[i])) i++; // Boşlukları atla

        start = i;

        if (!input[i]) break;

        // PIPE (|) karakterini işle
        if (input[i] == '|') {
            tail = (tail) ? (tail->next = new_token("|", TOKEN_PIPE)) : (head = new_token("|", TOKEN_PIPE));
            i++;
        }
        // Çift yönlendirme (">>", "<<") kontrolü
        else if (input[i] == '>') {
            if (input[i + 1] == '>') { // ">>" varsa
                tail = (tail) ? (tail->next = new_token(">>", TOKEN_REDIRECT_APPEND)) : (head = new_token(">>", TOKEN_REDIRECT_APPEND));
                i += 2;
            } else { // ">" ise
                tail = (tail) ? (tail->next = new_token(">", TOKEN_REDIRECT_OUT)) : (head = new_token(">", TOKEN_REDIRECT_OUT));
                i++;
            }
        }
        else if (input[i] == '<') {
            if (input[i + 1] == '<') { // "<<" varsa
                tail = (tail) ? (tail->next = new_token("<<", TOKEN_HEREDOC)) : (head = new_token("<<", TOKEN_HEREDOC));
                i += 2;
            } else { // "<" ise
                tail = (tail) ? (tail->next = new_token("<", TOKEN_REDIRECT_IN)) : (head = new_token("<", TOKEN_REDIRECT_IN));
                i++;
            }
        }
        // Çift veya tek tırnak içinde olan stringleri al
        else if (input[i] == '"' || input[i] == '\'') {
            char quote = input[i++];
            start = i;
            while (input[i] && input[i] != quote) i++;
            if (input[i] == quote) { // Kapanan tırnak bulunduğunda ekle
                char *token_value = strndup(&input[start], i - start);
                tail = (tail) ? (tail->next = new_token(token_value, (quote == '"') ? TOKEN_DQUOTE : TOKEN_SQUOTE)) :
                                (head = new_token(token_value, (quote == '"') ? TOKEN_DQUOTE : TOKEN_SQUOTE));
                free(token_value);
                i++;
            }
        }
        // Dolar değişkenlerini ($, $?) al
        else if (input[i] == '$') {
            start = i++;
            if (input[i] == '?') { // "$?" değişkeni
                i++;
            } else {
                while (isalnum(input[i]) || input[i] == '_') i++;
            }
            char *token_value = strndup(&input[start], i - start);
            tail = (tail) ? (tail->next = new_token(token_value, TOKEN_DOLLAR)) :
                            (head = new_token(token_value, TOKEN_DOLLAR));
            free(token_value);
        }
        // Normal kelimeleri al
        else {
            start = i;
            while (input[i] && !isspace(input[i]) && input[i] != '|' && input[i] != '<' && input[i] != '>') i++;
            char *token_value = strndup(&input[start], i - start);
            tail = (tail) ? (tail->next = new_token(token_value, TOKEN_WORD)) :
                            (head = new_token(token_value, TOKEN_WORD));
            free(token_value);
        }
    }

    return head;
}

void print_tokens(t_token *token) {
    while (token) {
        printf("Token: %-10s Type: %d\n", token->value, token->type);
        token = token->next;
    }
}

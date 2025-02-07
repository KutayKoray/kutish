#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "minishell.h"

t_token *new_token(char *value, t_token_type type) {
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
        while (isspace(input[i]))
            i++;

        start = i;

        if (input[i] == '|') 
		{
            tail = (tail) ? (tail->next = new_token("|", TOKEN_PIPE)) : (head = new_token("|", TOKEN_PIPE));
            i++;
        }
		else if (input[i] == '<') 
		{
            tail = (tail) ? (tail->next = new_token("<", TOKEN_REDIRECT_IN)) : (head = new_token("<", TOKEN_REDIRECT_IN));
            i++;
        }
		else if (input[i] == '>') 
		{
            tail = (tail) ? (tail->next = new_token(">", TOKEN_REDIRECT_OUT)) : (head = new_token(">", TOKEN_REDIRECT_OUT));
            i++;
        }
		else if (input[i] == '"' || input[i] == '\'') 
		{
            char quote = input[i++];
            start = i;
            while (input[i] && input[i] != quote)
                i++;
            if (input[i] == quote) 
			{ 
                tail = (tail) ? (tail->next = new_token(strndup(&input[start], i - start), (quote == '"') ? TOKEN_DQUOTE : TOKEN_SQUOTE)) : 
                        (head = new_token(strndup(&input[start], i - start), (quote == '"') ? TOKEN_DQUOTE : TOKEN_SQUOTE));
                i++;
            }
        } 
		else if (input[i] == '$') 
		{
			start = i;
			i++;

			if (input[i] == '?') 
			{
				i++;
				tail = (tail) ? (tail->next = new_token(strndup(&input[start], 2), TOKEN_DOLLAR)) :
								(head = new_token(strndup(&input[start], 2), TOKEN_DOLLAR));
			}
			else 
			{
				while (isalnum(input[i]) || input[i] == '_')
					i++;
				tail = (tail) ? (tail->next = new_token(strndup(&input[start], i - start), TOKEN_DOLLAR)) :
								(head = new_token(strndup(&input[start], i - start), TOKEN_DOLLAR));
			}
		}
		else if (input[i]) 
		{
            start = i;
            while (input[i] && !isspace(input[i]) && input[i] != '|' && input[i] != '<' && input[i] != '>')
                i++;
            tail = (tail) ? (tail->next = new_token(strndup(&input[start], i - start), TOKEN_WORD)) : 
                    (head = new_token(strndup(&input[start], i - start), TOKEN_WORD));
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


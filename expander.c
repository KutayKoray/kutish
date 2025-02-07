#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "minishell.h"

// $? değişkeninin genişletilmiş halini döndüren fonksiyon
static char *expand_exit_status() {
    int exit_status = 0; // TODO: Gerçek exit kodunu buraya ekle
    char *status_str = malloc(12);
    if (!status_str)
        return NULL;
    snprintf(status_str, 12, "%d", exit_status);
    return status_str;
}

// Token içinde $VAR olup olmadığını kontrol edip genişleten fonksiyon
static char *expand_variable(const char *token_value) {
    if (!token_value)
        return NULL;

    if (strncmp(token_value, "$?", 2) == 0) {
        return expand_exit_status();
    }

    char *result = strdup(token_value); // Varsayılan olarak token'ı kopyala
    char *dollar_pos = strchr(result, '$'); // $ işareti var mı?

    if (dollar_pos) {
        char *var_name = dollar_pos + 1; // $ sonrası değişken adı
        char *value = getenv(var_name);  // Çevresel değişkeni al

        if (value) {
            // Yeni genişletilmiş stringi oluştur
            size_t prefix_len = dollar_pos - result; // $'dan önceki kısmın uzunluğu
            size_t expanded_len = prefix_len + strlen(value) + 1;
            char *expanded = malloc(expanded_len);

            if (!expanded) {
                free(result);
                return NULL;
            }

            strncpy(expanded, result, prefix_len); // Önceki kısmı kopyala
            expanded[prefix_len] = '\0'; // String sonlandır
            strcat(expanded, value); // Değişken değerini ekle

            free(result);
            return expanded;
        } else {
            // Eğer değişken yoksa boş stringle değiştir
            free(result);
            return strdup("");
        }
    }

    return result;
}

// Tüm token listesini genişletir
void expand_variables(t_token *tokens) {
    t_token *current = tokens;

    while (current) {
        if (current->type == TOKEN_DOLLAR) { // Sadece $ içeren token'ları genişlet
            char *expanded_value = expand_variable(current->value);
            free(current->value); // Eski değeri temizle
            current->value = expanded_value; // Yeni değeri ata
            current->type = TOKEN_WORD; // Artık değişken genişledi, normal kelime oldu
        }
        current = current->next;
    }
}

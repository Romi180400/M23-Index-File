#include <stdio.h>
#include "trie/trie.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SPACES "\f\v\t "

struct trie_ctx {
    const char *string;
    int *lines_index;
    int line_index_counter;
    int capacity;
};

/* Function prototypes */
char *get_next_word(char *current, char **next);
void trie_ctx_cleanup(void *word_ctx, void *do_ctx);
void print_string(void *word_ctx, void *do_ctx);

char *my_strdup(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

char *get_next_word(char *current, char **next) {
    char *h;
    if (current == NULL)
        return NULL;
    while (isspace((unsigned char)*current)) current++;
    if (*current == '\0')
        return NULL;
    h = strpbrk(current, SPACES);
    if (h) {
        *h = '\0';
        h++;
        while (isspace((unsigned char)*h)) h++;
        *next = h;
    } else {
        *next = NULL;
    }
    return current;
}

void print_string(void *word_ctx, void *do_ctx) {
    struct trie_ctx *ctx = (struct trie_ctx *)word_ctx;
    int i;
    printf("%s appears in lines ", ctx->string);
    for (i = 0; i < ctx->line_index_counter - 1; i++) {
        printf("%d,", ctx->lines_index[i]);
    }
    printf("%d\n", ctx->lines_index[ctx->line_index_counter - 1]);
}

void trie_ctx_cleanup(void *word_ctx, void *do_ctx) {
    struct trie_ctx *ctx = (struct trie_ctx *)word_ctx;
    if (ctx != NULL) {
        free((char *)ctx->string);
        free(ctx->lines_index);
        free(ctx);
    }
}

int main() {
    struct trie_ctx *ctx_check;
    int line_counter = 1;
    char buffer[82] = {0};
    char *curr, *next;
    int *new_array = NULL;
    Trie strings_trie = trie();

    while (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        curr = buffer;
        while ((curr = get_next_word(curr, &next)) != NULL) {
            ctx_check = trie_exists(strings_trie, curr);
            if (ctx_check != NULL) {
                if (ctx_check->line_index_counter == ctx_check->capacity) {
                    ctx_check->capacity = ctx_check->capacity > 0 ? ctx_check->capacity * 2 : 2;

                    new_array = realloc(ctx_check->lines_index, ctx_check->capacity * sizeof(int));
                    if (new_array == NULL) {
                        fprintf(stderr, "Failed to allocate memory.\n");
                        exit(EXIT_FAILURE);
                    }
                    ctx_check->lines_index = new_array;
                }
                ctx_check->lines_index[ctx_check->line_index_counter++] = line_counter;
            } else {
                ctx_check = calloc(1, sizeof(struct trie_ctx));
                if (!ctx_check) {
                    fprintf(stderr, "Memory allocation failed for trie_ctx.\n");
                    exit(EXIT_FAILURE);
                }
                ctx_check->string = my_strdup(curr);
                ctx_check->lines_index = NULL;
                ctx_check->line_index_counter = 0;
                ctx_check->capacity = 2;
                ctx_check->lines_index = malloc(ctx_check->capacity * sizeof(int));
                if (!ctx_check->lines_index) {
                    fprintf(stderr, "Memory allocation failed for lines_index.\n");
                    exit(EXIT_FAILURE);
                }
                ctx_check->lines_index[ctx_check->line_index_counter++] = line_counter;
                trie_insert(strings_trie, curr, ctx_check);
            }
            curr = next;
        }
        line_counter++;
    }

    trie_iterate(strings_trie, print_string, NULL);
    trie_iterate(strings_trie, trie_ctx_cleanup, NULL);
    trie_destroy(&strings_trie);
    return 0;
}

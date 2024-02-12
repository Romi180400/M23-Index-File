#ifndef INDEX_H
#define INDEX_H

#include "trie/trie.h"
#include <stdio.h>
#include <stdlib.h>

#define SPACES "\f\v\t "

struct trie_ctx {
    const char *string;
    int *lines_index;
    int line_index_counter;
    int capacity;
};

/**
 * Duplicate a string using dynamic memory allocation.
 *
 * @param s The string to duplicate.
 * @return A pointer to the newly allocated string.
 */
char *my_strdup(const char *s);

/**
 * Extracts the next word from a string, given a set of delimiter characters.
 *
 * @param current The current position in the string.
 * @param next Pointer to the next word position in the string.
 * @return The next word extracted from the string.
 */
char *get_next_word(char *current, char **next);

/**
 * Prints the occurrences of a word along with the line numbers it appears on.
 *
 * @param word_ctx Context containing word and its occurrences.
 * @param do_ctx Additional context (unused in this function).
 */
void print_string(void *word_ctx, void *do_ctx);

/**
 * Cleans up dynamically allocated memory for a trie context.
 *
 * @param word_ctx The trie context to clean up.
 * @param do_ctx Additional context (unused in this function).
 */
void trie_ctx_cleanup(void *word_ctx, void *do_ctx);

#endif // INDEX_H


#ifndef INDEX_H
#define INDEX_H

#include "trie/trie.h"

void print_string(void *word_ctx, void *do_ctx);
char *get_next_word(char *current, char **next);
void trie_free(Trie trie);

#endif /* INDEX_H */


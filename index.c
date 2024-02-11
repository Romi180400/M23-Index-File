#include <stdio.h>
#include "trie/trie.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SPACES "\f\v\t "
struct trie_ctx {
    const char *string;
    int lines_index[100];
    int line_index_counter;
};

void print_string(void * word_ctx,void * do_ctx) {
    int i;
    struct trie_ctx * ctx;
    ctx = word_ctx;
    printf("%s appears in lines ",ctx->string);
    for(i=0;i<ctx->line_index_counter-1;i++) {
        printf("%d,",ctx->lines_index[i]);
    }
    printf("%d\n",ctx->lines_index[i]);
}
char * get_next_word(char * current,char **next) {
    char *h;
    if(current == NULL)
        return NULL;
    while(isspace(*current)) current++;
    if(*current == '\0')    
        return NULL;
    h = strpbrk(current,SPACES);
    if(h)  {
        *h = '\0';
        h++;
        while(isspace(*h)) h++;
        *next = h;
    }
    else {
        *next = NULL;
    }
    return current;
}
int main() {
    struct trie_ctx * ctx_check;
    char buffer[82] = {0};
    int line_counter =1;
    char * curr, * next;
    Trie strings_trie = trie();
    while(fgets(buffer,sizeof(buffer),stdin)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        curr = buffer;
        while((curr = get_next_word(curr,&next)) != NULL) {
            ctx_check = trie_exists(strings_trie,curr);
            if(ctx_check != NULL) {
                ctx_check->lines_index[ctx_check->line_index_counter++] = line_counter;
            }else { 
                ctx_check = calloc(1,sizeof(struct trie_ctx));
                ctx_check->string = strcpy(malloc(strlen(curr) + 1 ),curr);
                ctx_check->lines_index[ctx_check->line_index_counter++] = line_counter;
                trie_insert(strings_trie,curr,ctx_check);
            }
            curr = next;
        }
        line_counter++;
    }
    trie_iterate(strings_trie,print_string,NULL);
    return 0;
}
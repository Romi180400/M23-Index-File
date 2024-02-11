#include "../trie.h"
#include <stdio.h>
void my_do_function(void *word_ctx,void * do_ctx) {
    /* just print the word*/
    printf("%s\n",(char*)word_ctx);
}
int main() {
    int i;
    Trie t;
    const char *f;
    const char *strings[4] = {
        "yarin",
        "hello",
        "hellow",
        "hellno"
    };
    t = trie();
    for(i=0;i<4;i++) {
        trie_insert(t, strings[i], (char*)strings[i]);
    }
    for(i=0;i<4;i++) {
        f = trie_exists(t, strings[i]);
        if(f != NULL) {
            printf("%s\n",f);
        }
        else {
            printf("string:'%s' could not be found.\n",strings[i]);
        }
    }
    /* display all words in the tree by lexicographical order*/
    printf("printing names in trie:\n");
    trie_iterate(t,my_do_function,NULL);
    printf("printing ends here\n");
    trie_delete(t, strings[1]);
    for(i=0;i<4;i++) {
        f = trie_exists(t, strings[i]);
        if(f != NULL) {
            printf("%s\n",f);
        }
        else {
            printf("string:'%s' could not be found.\n",strings[i]);
        }
    }
    trie_destroy(&t);
    return 0;
}
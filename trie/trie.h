/**
 * @file trie.h
 * @author Yarin Avisidris (yarinavisidris100.com)
 * @brief API header for Trie implementation in C.
 * @version 0.1
 * @date 2023-05-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __TRIE_H_
#define __TRIE_H_

typedef struct trie * Trie;

/**
 * @brief create and returns a new Trie data structure.
 * 
 * @return Trie 
 */
Trie trie();

/**
 * @brief 
 * 
 * @param trie reference to the Trie structure.
 * @param string the string to insert in the trie.
 * @param end_of_str_ctx the string context (a pointer that gives a meaning to this string, WARN: should not be NULL!) 
 * @return const char* returns pointer to inserted string ( string ) 
 */
const char * trie_insert(Trie trie,const char *string,void * end_of_str_ctx);

/**
 * @brief 
 *  
 * @param trie 
 * @param string 
 * @return void* returns pointer to trie context 
 */
void * trie_exists(Trie trie,const char *string);

/**
 * @brief deletes a string in the Trie data structure.
 * 
 * @param trie reference to the Trie structure.
 * @param string the string to insert in the trie.
 */
void trie_delete(Trie trie,const char  *string);

/**
 * @brief completely deallocates all memory for the Trie.
 * 
 * @param trie 
 */
void trie_destroy(Trie * trie);


/**
 * @brief function for iterating the trie tree.
 * 
 * @param trie the trie
 * @param do_function a function that does something to the word in the tree, this is completely generic ( for example can be used for printing)
 * @param do_ctx the context for the do function ( sometimes we want to add contex to the operation )
 */
void trie_iterate(Trie trie, void (*do_function)(void * word_ctx,void * do_ctx),void * do_ctx);




#endif

#ifndef TRIE_H
#define TRIE_H

#define HASHSIZE 26
#define ALLIEN 97
#define BUFLEN 512

typedef struct dict dict ;
typedef struct Trie Trie ;

typedef enum
{
	false = 0,
	true = 1
} bool ;


/*** For dictionary node structure ***/
struct dict
{
	char key ;
	Trie* trieNode ;
	dict* next ;
} ;


/*** For trie node structure ***/
struct Trie
{
	char* string ;
	dict** children ;
	bool isWord ;
} ;


char* subStr(char*, int) ;

/*** For dictionary related subroutines ***/
int hash(char) ;
dict** dictCreator() ;
dict* createDictItem(char, Trie*) ;
Trie* insert(dict**, char, char*) ;
Trie* search(dict**, char) ;

/*** For trie node subroutines ***/
Trie* createTrieNode(char*) ;
Trie* trieCreate() ;
void trieInsert(Trie*, char*) ;
bool trieSearcher(Trie*, char*, bool) ;
bool trieSearch(Trie*, char*) ;
bool trieStartsWith(Trie*, char*) ;
void trieFree(Trie*) ;







#endif

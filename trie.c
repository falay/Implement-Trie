#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"


int hash(char key)
{
	return key-ALLIEN ;
}

dict** dictCreator()
{
	dict** newDict = (dict**)malloc( sizeof(dict*)*HASHSIZE ) ;
	for(int i=0; i<HASHSIZE; i++)
		newDict[i] = (dict*)NULL ;
	return newDict ;
}


dict* createDictItem(char key, Trie* trieNode)
{
	dict* item = (dict*)malloc( sizeof(dict) ) ;
	item->key = key ;
	item->trieNode = trieNode ;
	item->next = NULL ;
	
	return item ;
}


Trie* insert(dict** myDict, char key, char* subStr)
{
	Trie* insertedTrieNode = createTrieNode( subStr ) ;
	int index =  hash(key) ;
	dict* head = myDict[index] ;
	while( head != NULL )
	{
		if( head->key == key )
		{	
			free( head->trieNode ) ;
			head->trieNode = insertedTrieNode ;
			return insertedTrieNode;
		}
		head = head->next ;
	}		
	
	dict* oldHead = myDict[index] ;
	myDict[index] = createDictItem( key, insertedTrieNode ) ;
	myDict[index]->next = oldHead ;
	
	return insertedTrieNode ;
}


Trie* search(dict** myDict, char key)
{
	dict* head = myDict[ hash( key ) ] ;
	while( head != NULL )
	{
		if( head->key == key )
			return head->trieNode ;
		head = head->next ;
	}
	return (Trie*)NULL ;
}


/** Initialize your data structure here. */
Trie* trieCreate() 
{
    return createTrieNode("") ;
}


Trie* createTrieNode(char* string)
{
	Trie* newTrieNode = (Trie*)malloc( sizeof(Trie) ) ;
	newTrieNode->string = strdup( string ) ;
	newTrieNode->children = dictCreator() ;
	newTrieNode->isWord = false ;
	
	return newTrieNode ;
}

char* subStr(char* word, int len)
{
	char* subWord = strdup( word ) ;
	subWord[ len ] = '\0' ;
	return subWord ;
}

/** Inserts a word into the trie. */
void trieInsert(Trie* root, char* word) 
{
	Trie* currentNode = root ;
	int strLen = strlen( word ) ;
    for(int i=0; i<strLen; i++)
	{
		Trie* trieNode ;
		if( (trieNode = search(currentNode->children, word[i])) == (Trie*)NULL )
			trieNode = insert( currentNode->children, word[i], subStr(word, i+1) ) ;
		currentNode = trieNode ;
	}
	currentNode->isWord = true ;
}


bool trieSearcher(Trie* root, char* string, bool isWord)
{
	Trie* currentNode = root ;
	int strLen = strlen( string ) ;
    for(int i=0; i<strLen; i++)
	{
		Trie* trieNode ;
		if( (trieNode = search(currentNode->children, string[i])) == (Trie*)NULL )
			return false ;
		currentNode = trieNode ;
	}	
	
	if( isWord )
		return currentNode->isWord ;
	else
		return true ;
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* root, char* word) 
{
    return trieSearcher( root, word, true ) ;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* root, char* prefix) 
{
    return trieSearcher( root, prefix, false ) ;
}

void trieFree(Trie* root) 
{
	for(int i=0; i<HASHSIZE; i++)
	{
		dict* dictHead = root->children[i] ;
		while( dictHead != NULL )
		{
			trieFree( dictHead->trieNode ) ;
			dictHead = dictHead->next ;
		}
	}	
	free( root ) ;
}

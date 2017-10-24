#include <stdlib.h>
#include <stdio.h>
#include "trie.h"

int main()
{
	Trie* root = trieCreate() ;
	
	bool param_1 = trieSearch(root, "a");	
	trieInsert( root, "word" ) ;
	trieInsert( root, "worder" ) ;
	bool param_2 = trieSearch(root, "worder");
	bool param_3 = trieStartsWith(root, "wor");
	
	trieFree(root);
	
	printf("%d%d%d\n", param_1, param_2, param_3) ;
	
	return 0 ;
}
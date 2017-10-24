all: 
	gcc main.c trie.c -o trie

clean:
	rm -rf *.o trie
CFLAGS = -ansi -pedantic -Wall -g -fsanitize=address

index.out: index.o trie.o
	gcc $(CFLAGS) $^ -o $@

index.o: index.c trie/trie.h
	gcc $(CFLAGS) -c $<

trie.o: trie/trie.c trie/trie.h
	gcc $(CFLAGS) -c $<

clean:
	rm -f index.out index.o trie.o

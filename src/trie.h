#ifndef TRIE_H
#define TRIE_H

#include "main.h"

struct TrieNode * createNode();

int freeTrie(TrieNode * trie);

Trie * initTrie(int fallback);

int insertTrie(Trie * trie,char * str,TokenType type,unsigned char val);

TokenType getType(Trie * trie,char * str);

int findTrie(Trie *trie,char * str);

int isAlpha(char * str);
#endif

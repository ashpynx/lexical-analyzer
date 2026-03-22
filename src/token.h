#ifndef TOKEN_H
#define TOKEN_H
#include "main.h"



Lexer *
init_lexer(char * source);

Token 
next_token(Trie * ,Lexer * );

TokenArray* 
push_token(TokenArray* array,Token tok);

TokenArray* 
init_tokenarray();

int 
is_keyword(Trie * trie ,struct word * w);

int 
is_symbol(Trie * trie,struct word * w);

int
is_identifier(struct word * w);

int 
is_lvalue(struct word * w);

#endif

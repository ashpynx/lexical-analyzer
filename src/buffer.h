#ifndef BUF_H
#define BUF_H

#include "main.h"

char *
read_file(char * fname);

struct word
next_word(Lexer * lex);

void 
print_help();

struct word  
get_word(char * root);


#endif

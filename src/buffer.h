#ifndef BUF_H
#define BUF_H

#include "main.h"

char *
read_file(char * fname);

struct word
next_word(Lexer * lex);

#endif

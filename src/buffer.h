#ifndef BUF_H
#define BUF_H
#include "token.h"

char *
read_file(char * fname);

struct word
next_word(const char * buf);

#endif

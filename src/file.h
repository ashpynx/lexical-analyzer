#ifndef FILE_H
#define FILE_H

#include <stdio.h>

#include "token.h"

#include <stddef.h>
typedef struct file
{
    FILE * fptr;
    //if we will output binary or text
    int bin;
}file;


void file_push(file * file_struct,TokenArray * token_array );


#endif

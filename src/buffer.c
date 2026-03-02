#include <stdlib.h>

#include <stdio.h>

#include "buffer.h"

char * 
read_file(char * filename)
{

    FILE * file = fopen(filename,"r");

    if(file==NULL)
    {
        printf("Could not read file '%s'\n",filename);
        exit(74);
    }

    fseek(file,0L,SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char *buffer =malloc(size+1);
    
    if(buffer==NULL)
    {
        printf("Error managing buffer of file '%s'\n",filename);
        exit(74);
    }

    for(int i=0;i<size+1;i++)
    {
        buffer[i] = fgetc(file);
    }

    buffer[size] = '\0';

    fclose(file);

    return buffer;
}

struct word
next_word(const char* buf)

{
    int len=0;
    int i=0;
    while(buf[i]==' ' || buf[i] == '\n' || buf[i] =='\t')
        i++;

    while(buf[i+len] != '\0' && (buf[i+len]!='\n' && buf[i+len]!=' ' && buf[i+len]!='\t'))       
        len++;
    
    
    return (struct word){buf+i,len};
}


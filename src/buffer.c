#include <stdlib.h>

#include <stdio.h>

#include "buffer.h"


//put file into a string
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

//not used anymore,here for museum purposes
struct word
next_word(Lexer * lex)

{
    const char * buf = lex->curr;
    int len=0;
    int i=0;
    int negi=0;
    while(buf[i]==' ' || buf[i] == '\n' || buf[i] =='\t' || buf[i] == '\0')
    {
        if(buf[i]=='\n')
        {
            lex->line++;
            lex->position=0;
            negi=i+1;
        }
        if(buf[i]=='\0')
        {
            return (struct word){NULL,0};
        }
        i++;
    }
    while(buf[i+len] != '\0' && (buf[i+len]!='\n' && buf[i+len]!=' ' && buf[i+len]!='\t'))       
        len++;
     
    lex->curr = lex->curr + i +len;
    lex->position += i-negi+len; 
    return (struct word){buf+i,len};
}

void 
print_help()
{
    printf("\n\nlexical analyser\n\nUsage:\n\n");
    printf("./lex -i [source file] [files] : analyses [files] according to [source file]\n\n");
    printf("-i [source file] : indicates the source file for the lexer\n\n"); 

}

//for source file
struct word
get_word(char * root)
{
    int total=0;
    while(root[0]!='\0' && isspace(root[0]))
    {
        root++;
        total++;
    }
    int j=0;
    while(root[j]!='\0' && !isspace(root[j]))
    {
        j++;
    }
    if(j==0)
        return (struct word){NULL,0};
    
    char * buf = malloc(j+1);

    memcpy(buf,root,j);
    buf[j]='\0';

    
    return (struct word){.head = buf,.length=total+j};

}

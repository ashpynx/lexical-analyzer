#include <stdio.h>
#include "token.h"
#include "buffer.h"

int 
main(int argc
    ,char * argv[])
{
    

    char * buffer;
    

    if(argc <= 1)
    {
        perror("Not Enough arguments!\n");
        exit(0);
    }
        
    
    buffer = read_file(argv[1]);

    TokenArray  arr;

    Lexer * lex = init_lexer(buffer);
    
    struct word hi=next_word(lex->head);

    printf("%.*s\n",hi.length,hi.head);

    printf("%s",lex->head);

}

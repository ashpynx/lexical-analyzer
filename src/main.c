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
    for (int i=0; i<3;i++)
    {
        Token newtoken = next_token(lex);

        if(newtoken.type == __KEYWORD)
        {
            printf("Keyword found at line %d , position %d:%.*s\n",newtoken.line,newtoken.position,newtoken.length,newtoken.head);

        }
    }
}

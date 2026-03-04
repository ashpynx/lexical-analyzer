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

    Lexer * lex = init_lexer(buffer);
    
    TokenArray * tokarr = init_tokenarray();
    
    Token temp;
    while(1)
    {
        temp = next_token(lex);

        if(lex->state == __EOF)
        {
            break;
        }
        
        tokarr = push_token(tokarr,temp);

        if(temp.type ==__KEYWORD)
        {
            printf("Keyword found at line %d , position %d:%.*s\n",temp.line,temp.position,temp.length,temp.head);
        }
    }


}

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
    }
    for(int i=0;i<tokarr->length;i++)
    {
        Token temp1=tokarr->arr[i]; 
        if(temp1.type ==__KEYWORD)
        {
            printf("Keyword found at line %d , position %d:%.*s\n",temp1.line,temp1.position,temp1.length,temp1.head);
        }else if (temp1.type == __SYMBOL)
        {
            printf("Symbol found at line %d , position %d:%.*s\n",temp1.line,temp1.position,temp1.length,temp1.head);
        }
        else if(temp1.type == __LVALUE)
        {

            printf("Value found at line %d , position %d:%.*s\n",temp1.line,temp1.position,temp1.length,temp1.head);

        }
        else if (temp1.type == __ID)
        {

            printf("Identifier found at line %d , position %d:%.*s\n",temp1.line,temp1.position,temp1.length,temp1.head);
        }
        else 
        {
            printf("Unidentifiable token found at line %d , position %d:%.*s\n",temp1.line,temp1.position,temp1.length,temp1.head);
        }
    }
    free(buffer);
    free(lex);
    free(tokarr->arr);
    free(tokarr);
    return 0;
}

#include <stdio.h>
#include "main.h"
#include "trie.h"
#include "buffer.h"
#include "token.h"

int 

main(int argc
    ,char * argv[])
{
    
    Trie * obj = initTrie();

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
        temp = next_token(obj,lex);

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
            printf("\e[38;2;200;50;50mKeyword\e[0m found at line %d , position %d:\e[38;2;200;50;50m%.*s\e[0m\n",temp1.line,temp1.position,temp1.length,temp1.head);
        }else if (temp1.type == __SYMBOL)
        {
            printf("\e[38;2;255;155;100mSymbol\e[0m found at line %d , position %d:\e[38;2;255;155;100m%.*s\e[0m\n",temp1.line,temp1.position,temp1.length,temp1.head);
        }
        else if(temp1.type == __LVALUE)
        {
            printf("\e[38;2;0;255;0mValue\e[0m found at line %d , position %d:\e[38;2;0;255;0m%.*s\e[0m\n",temp1.line,temp1.position,temp1.length,temp1.head);
        }
        else if (temp1.type == __ID)
        {

            printf("\e[38;2;10;200;210mIdentifier\e[0m found at line %d , position %d:\e[38;2;10;200;210m%.*s\e[0m\n",temp1.line,temp1.position,temp1.length,temp1.head);
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
   free(obj);
   
   return 0;
}   

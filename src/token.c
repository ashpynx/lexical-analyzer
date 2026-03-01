#include "token.h"

const char * keywords[] = {"IF","INT","FLOAT"};

Lexer * init_lexer(const char * source)
{

    Lexer *newLexer = (Lexer*)malloc(sizeof(Lexer));

    newLexer->head = source;
    newLexer->curr = source;
    newLexer->line=0;
    newLexer->position=0;

    return newLexer;
}

TokenArray* push_token(TokenArray* array)
{
    if(array->length == array->capacity)
    {
        array->arr = (Token *)realloc(array->arr,array->capacity*2);
        if(array->arr == NULL)
        {
            fprintf(stderr,"Could'n allocate more for Token Array!\nExiting...");
            exit(74);
        }
        
        array->capacity *=2;


    }


    return array;
}


Token next_token( Lexer * lex)
{
    
    Token temp;

    


    return temp;
}

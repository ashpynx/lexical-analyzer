#include "token.h"
#include "buffer.h"
const char * keywords[] = {"IF","INT","FLOAT"};

Lexer * 
init_lexer(const char * source)
{

    Lexer *newLexer = (Lexer*)malloc(sizeof(Lexer));

    newLexer->head = source;
    newLexer->curr = source;
    newLexer->line=0;
    newLexer->position=0;

    return newLexer;
}

TokenArray* 
push_token(TokenArray* array)
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


Token
next_token( Lexer * lex)
{
    
    Token temp;

    struct word nw  = next_word(lex);    

    if(is_keyword(&nw))
    {
        temp.head = nw.head ;
        temp.length = nw.length;
        temp.type = __KEYWORD;
        temp.line = lex->line;
        temp.position = lex->position - temp.length;

    }

    return temp;
}

int
is_keyword(struct word *w)
{

    int len = sizeof(keywords)/sizeof(char*);

    for(int i=0;i<len;i++)
    {
        int bol=1;

        for(int j=0;j<w->length;j++)
        {
            if(w->head[j]!=keywords[i][j])
            {
                bol=0;
                break;
            }

        }
        if(bol==1)
        {
            return 1;
        }
    }
    return 0;
}

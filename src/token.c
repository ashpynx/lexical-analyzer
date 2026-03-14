#include "token.h"
#include "buffer.h"
const char * keywords[] = {"IF","INT","FLOAT","WHILE","FUNC","END"};

const char symbols[] = {'+','=','-','/','*','(',')','[',']','{','}'};



Lexer * 
init_lexer(char * source)
{

    Lexer *newLexer = (Lexer*)malloc(sizeof(Lexer));

    newLexer->head = source;
    newLexer->curr = source;
    newLexer->line=0;
    newLexer->position=0;

    return newLexer;
}

TokenArray* 
push_token(TokenArray* array,Token tok)
{
    if(array->length == array->capacity)
    {
        array->arr = realloc(array->arr,(array->capacity)*sizeof(Token)*2);
        if(array->arr == NULL)
        {
            fprintf(stderr,"Couldn't allocate more for Token Array!\nExiting...");
            exit(74);
        }
        
        array->capacity *=2;

    }

    array->arr[array->length] = tok;
    
    array->length++;
    return array;
}


Token
next_token( Lexer * lex)
{
    
    Token temp;
    struct word nw  = next_word(lex);    



    if(nw.head ==NULL)
    {
        lex->state = __EOF;
        return temp;
    }


    if(is_keyword(&nw))
    {
        temp.head = nw.head ;
        temp.length = nw.length;
        temp.type = __KEYWORD;
        temp.line = lex->line;
        temp.position = lex->position - temp.length;

    }
    else if(is_symbol(&nw))
    {
        temp.head = nw.head ;
        temp.length = 1;
        temp.type = __SYMBOL;
        temp.line = lex->line;
        temp.position = lex->position - 1;
    }
    else if(is_lvalue(&nw))
    {
        temp.head = nw.head;
        temp.length=nw.length;
        temp.type=__LVALUE;
        temp.line=lex->line;
        temp.position = lex->position - temp.length;

    }
    else if(is_identifier(&nw))
    {
        temp.head = nw.head;
        temp.length = nw.length;
        temp.type = __ID;
        temp.line = lex->line;
        temp.position = lex->position-nw.length;
    }
    else 
    {

        temp.length =nw.length;
        temp.head = nw.head;
        temp.line =lex->line;
        temp.position = lex->position - nw.length;
        temp.type = __UNID;

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




TokenArray*
init_tokenarray()
{
    TokenArray * temp = (TokenArray*)malloc(sizeof(TokenArray));

    temp->arr = (Token*)malloc(sizeof(Token));

    temp->capacity =1;
    temp->length = 0;

    return temp;
}

int
is_symbol(struct word *w)
{
    if(w->length !=1)
        return 0;

    int len = sizeof(symbols)/sizeof(char);

    for(int i=0;i<len;i++)
    {
        if(*(w->head) == symbols[i])
        {
            return 1;
        }
    }
    return 0;
}

int 
is_identifier(struct word * w)
{
    struct word temp = *w;

    temp.length =1;
    for(int i=0; i < w->length; i++)
    {
        temp.head++;
        if(is_symbol(&temp))
            return 0;

    }
    
    return 1;
}

int
is_lvalue(struct word * w)
{
    int val=1;
    if(w->head[0]=='0')
    {
        if(w->length!=1)
        {
            val=0;

            goto chr;
        }
    }
    for(int i=0 ; i< w->length;i++)
    {
        if(!(w->head[i] - '0' >= 0 && w->head[i] - '0' <=9))
        {
            val=0;
            break;
        }
    }
    
    chr:


    return val;
}

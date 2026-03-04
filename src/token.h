#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

#include <stdio.h>

extern const char * keywords[];


struct word 
{
    const char * head;
    int length;
};

typedef enum 
{
    
    __Available,
    __EOF

}LexerState;


typedef enum 
{
    
    __KEYWORD,
    __ID,
    __VALUE,

}TokenType;


typedef struct 
{

    TokenType type;

    const char * head;
    
    int length;

    int position;
    
    int line;

}Token;

typedef struct 
{

    Token * arr;

    size_t length;

    size_t capacity;

}TokenArray;

typedef struct 
{

    char * head;

    char * curr;

    int line;

    int position;

    LexerState state;

}Lexer;


Lexer *
init_lexer(const char * source);

Token 
next_token(Lexer * );

TokenArray* 
push_token(TokenArray* array,Token tok);

TokenArray* 
init_tokenarray();


int 
is_keyword(struct word * w);

#endif

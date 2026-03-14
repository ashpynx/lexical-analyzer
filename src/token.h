#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

#include <stdio.h>

extern const char * keywords[];

extern const char symbols[];

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
    __LVALUE,
    __SYMBOL,
    __UNID,
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
init_lexer(char * source);

Token 
next_token(Lexer * );

TokenArray* 
push_token(TokenArray* array,Token tok);

TokenArray* 
init_tokenarray();

int 
is_keyword(struct word * w);

int 
is_symbol(struct word * w);

int
is_identifier(struct word * w);

int 
is_lvalue(struct word * w);

#endif

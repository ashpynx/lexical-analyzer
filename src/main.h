#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <ctype.h>

typedef enum 
{
    __IF=1,
    __WHILE,
    __FUNCTION,
    __INT,
    __FLOAT,
    __STRING,
    __END

}kwType;

typedef enum 
{
    __ADD = 8,
    __POSTADD,
    __PREADD,
    __SEMICOLON,
    __SUB,
    __POSTSUB,
    __PRESUB,
    __INEQ,
    __EQUALITY,
    __ASSIGN,
    __MORE,
    __LESS,
    __DIV,
    __MULT,
    __LPARAN,
    __RPARAN,
    __LCLOSED,
    __RCLOSED,
    __LCURLY,
    __RCURLY,

}syType;

typedef enum 
{
    __VALINT,
    __VALFLOAT,
    __VALSTRING

}LVALUETYPE;

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
    __NONE, 
    __KEYWORD,
    __ID,
    __LVALUE,
    __SYMBOL,
    __UNID,
}TokenType;


typedef struct 
{

    TokenType type;

    unsigned char val;

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

typedef struct TrieNode
{
    struct TrieNode *nodes[128];
    
    TokenType  type;

    unsigned char val;

}TrieNode;

typedef struct 
{

    struct TrieNode * head;

    int size;

}Trie;





#endif

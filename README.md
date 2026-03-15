# lexical-analyzer

This litte implementation of a practical lexical analyzer lets you break down a file into parts(tokens).

_current build:_

keywords :  {"IF","INT","FLOAT","WHILE","FUNC","END"};

symbols  :  {"+","-","!=","==","=",">","<","/","*","(",")","[","]","{","}"};

the program also supports integer and float values , and identifiers (no symbols and no numbers as first character).

# Usage

Compile the program with **make** and input any file you want, it will output the tokens into stdout.
currently only supports stdout so no support for saving into file for now.

Also, the program doesnt work great unless you put spaces between tokens(this is because of my laziness).I plan to fix this in the future.

# Example Input & Output

with the file **test**
{

    FUNC HELLO ( FLOAT X )
    
        IF ( X == 5,50 )
    
            PRINTF LEXER
    
        END
    
    END

}

the output is
{

    Keyword found at line 0 , position 0:FUNC
    Identifier found at line 0 , position 5:HELLO
    Symbol found at line 0 , position 11:(
    Keyword found at line 0 , position 13:FLOAT
    Identifier found at line 0 , position 19:X
    Symbol found at line 0 , position 21:)
    Keyword found at line 2 , position 4:IF
    Symbol found at line 2 , position 7:(
    Identifier found at line 2 , position 9:X
    Symbol found at line 2 , position 12:==
    Value found at line 2 , position 14:5,50
    Symbol found at line 2 , position 19:)
    Identifier found at line 4 , position 8:PRINTF
    Identifier found at line 4 , position 15:LEXER
    Keyword found at line 6 , position 4:END
    Keyword found at line 8 , position 0:END

}

You can change the keywords and symbols to whatever you want by changing the elements in arrays **keywords** and **symbols** in top of the file **src/token.c**.




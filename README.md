# lexical-analyzer

This litte implementation of a practical lexical analyzer lets you break down a file into parts(tokens).

_Defaults:_

keywords :  {"if","int","float","string","while","function","end"};

symbols  :  {" +" , "++" , "-" , "--" , "\*" , "/" , "!=" , "==" , "=" , ">" , "<" , "," , "(" , ")" , "\[" , "\] " , "\{" , "\}" };

the program also supports lvalues (ints,strings and floats) and identifiers (no symbols and no numbers as first character).

# Usage

Compile the program with **make** and input any file you want, it will output the tokens into stdout.
currently only supports stdout so no support for saving into file for now.

# Example Input & Output
with the file **test**
{

    function main(int x)

        if(x==15)
            printf "Hello,World!\n";
    
    
        float y = x*5;
    
        string str = "y";


    end

}

the output  of **.lex test**
{

    -i option not found.fallback to defaults.-h for more info. 
     
     
     
    File: test 
     
    Keyword found at line 0 , position 0:function 
    Identifier found at line 0 , position 9:main 
    Symbol found at line 0 , position 13:( 
    Keyword found at line 0 , position 14:int 
    Identifier found at line 0 , position 18:x 
    Symbol found at line 0 , position 19:) 
    Keyword found at line 2 , position 4:if 
    Symbol found at line 2 , position 6:( 
    Identifier found at line 2 , position 7:x 
    Symbol found at line 2 , position 8:== 
    Value found at line 2 , position 10:15 
    Symbol found at line 2 , position 12:) 
    Identifier found at line 3 , position 8:printf 
    Value found at line 3 , position 16:"Hello,World!\n" 
    Symbol found at line 3 , position 31:; 
    Keyword found at line 6 , position 4:float 
    Identifier found at line 6 , position 10:y 
    Symbol found at line 6 , position 12:= 
    Identifier found at line 6 , position 14:x 
    Symbol found at line 6 , position 15: * 
    Value found at line 6 , position 16:5 
    Symbol found at line 6 , position 17:; 
    Keyword found at line 8 , position 4:string 
    Identifier found at line 8 , position 11:str 
    Symbol found at line 8 , position 15:= 
    Value found at line 8 , position 18:"y" 
    Symbol found at line 8 , position 20:; 
    Keyword found at line 11 , position 0:end

        
}

# Customization
You can customize the lexer into analysing the file into your liking.You can do it by feeding the program a source file.
which is done like this:

File:source.txt
{

    #   This is a default source file and it contains same tokens as the defaults of the lexer.
    #   #'s are comments,
    #   you can do %s %s %d on each line,
    #   %s->token's string %s-> token type's string(keyword or symbol) %d->token's value(optional) 
    #   if %d is not given, the lexer will automatically assign a value
    #
    
    #keywords
    if keyword 
    int keyword
    float keyword
    string keyword
    while keyword
    function keyword
    end keyword
    
    #symbols
    , symbol
    -- symbol
    ++ symbol
    + symbol
    ; symbol
    - symbol
    != symbol
    == symbol
    = symbol
    > symbol
    < symbol
    / symbol
    * symbol
    ( symbol
    ) symbol
    [ symbol
    ] symbol
    { symbol
    } symbol
    
}
if run as **.lex -i source.txt test**

{

    File: test 
     
    Keyword found at line 0 , position 0:function 
    Identifier found at line 0 , position 9:main 
    Symbol found at line 0 , position 13:( 
    Keyword found at line 0 , position 14:int 
    Identifier found at line 0 , position 18:x 
    Symbol found at line 0 , position 19:) 
    Keyword found at line 2 , position 4:if 
    Symbol found at line 2 , position 6:( 
    Identifier found at line 2 , position 7:x 
    Symbol found at line 2 , position 8:== 
    Value found at line 2 , position 10:15 
    Symbol found at line 2 , position 12:) 
    Identifier found at line 3 , position 8:printf 
    Value found at line 3 , position 16:"Hello,World!\n" 
    Symbol found at line 3 , position 31:; 
    Keyword found at line 6 , position 4:float 
    Identifier found at line 6 , position 10:y 
    Symbol found at line 6 , position 12:= 
    Identifier found at line 6 , position 14:x 
    Symbol found at line 6 , position 15: * 
    Value found at line 6 , position 16:5 
    Symbol found at line 6 , position 17:; 
    Keyword found at line 8 , position 4:string 
    Identifier found at line 8 , position 11:str 
    Symbol found at line 8 , position 15:= 
    Value found at line 8 , position 18:"y" 
    Symbol found at line 8 , position 20:; 
    Keyword found at line 11 , position 0:end

}


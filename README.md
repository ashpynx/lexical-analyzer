# lexical-analyzer

This litte implementation of a practical lexical analyzer lets you break down a file into parts(tokens).

_current build:_

keywords :  {"if","int","float","string","while","function","end"};

symbols  :  {"+","++","-","--","!=","==","=",">","<","/","*","(",")","[","]","{","}"};

the program also supports lvalues (ints,strings and floats) and identifiers (no symbols and no numbers as first character).

# Usage

Compile the program with **make** and input any file you want, it will output the tokens into stdout.
currently only supports stdout so no support for saving into file for now.


# Example Input & Output

with the file **test**
{

    int function hello ()

        int x = 5;
    
        string v = "Hello,World!";

        while(x==5)

            printf x ++;

        printf v;

    end

}

the output is
{

    Keyword found at line 0 , position 3:int
    Keyword found at line 0 , position 12:function
    Identifier found at line 0 , position 18:hello
    Symbol found at line 0 , position 20:(
    Symbol found at line 0 , position 21:)
    Keyword found at line 2 , position 7:int
    Identifier found at line 2 , position 9:x
    Symbol found at line 2 , position 12:=  
    Value found at line 2 , position 13:5
    Symbol found at line 2 , position 14:;
    Keyword found at line 4 , position 10:string
    Identifier found at line 4 , position 12:v
    Symbol found at line 4 , position 15:=  
    Value found at line 4 , position 29:"Hello,World!"
    Symbol found at line 4 , position 30:;
    Keyword found at line 6 , position 9:while
    Symbol found at line 6 , position 10:(
    Identifier found at line 6 , position 11:x
    Symbol found at line 6 , position 13:==
    Value found at line 6 , position 14:5
    Symbol found at line 6 , position 15:)
    Identifier found at line 8 , position 14:printf
    Identifier found at line 8 , position 16:x
    Symbol found at line 8 , position 19:++
    Symbol found at line 8 , position 20:;
    Identifier found at line 10 , position 10:printf
    Identifier found at line 10 , position 12:v
    Symbol found at line 10 , position 13:;
    Keyword found at line 12 , position 3:end\
    
}

you can change the keywords and symbols however you like by editing the function initTrie() in src/trie.c.
leave insertTrie()'s first parameter as is,change the string to whatever you like,change the third parameter to __KEYWORD or __SYMBOL depending on what you want to do, and the last parameter is value of symbol or keyword,currently it has no use so you can put garbage values for it. 





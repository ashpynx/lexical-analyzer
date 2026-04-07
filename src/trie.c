#include "trie.h"
#include "main.h"

Trie *
initTrie(int fallback)

{
    Trie * temp;
        
    temp = malloc(sizeof(Trie));

    if(temp==0)
    {
        perror("initTree:Couldn't Allocate Memory!\n");
        exit(74);
    }
   
    temp->size =0;

    temp ->head = createNode();
    //if no -i, add defaults
    if(fallback)
    {
        insertTrie(temp,"if",__KEYWORD,__IF);
        insertTrie(temp,"int",__KEYWORD,__INT);
        insertTrie(temp,"float",__KEYWORD,__FLOAT);
        insertTrie(temp,"string",__KEYWORD,__STRING);
        insertTrie(temp,"while",__KEYWORD,__WHILE);
        insertTrie(temp,"function",__KEYWORD,__FUNCTION);
        insertTrie(temp,"end",__KEYWORD,__END);

        insertTrie(temp,"--",__SYMBOL,__POSTSUB);
        insertTrie(temp,"++",__SYMBOL,__POSTADD);
        insertTrie(temp,"+",__SYMBOL,__ADD);
        insertTrie(temp,";",__SYMBOL,__SEMICOLON);
        insertTrie(temp,"-",__SYMBOL,__SUB);
        insertTrie(temp,"!=",__SYMBOL,__INEQ);
        insertTrie(temp,"==",__SYMBOL,__EQUALITY);
        insertTrie(temp,"=",__SYMBOL,__ASSIGN);
        insertTrie(temp,">",__SYMBOL,__MORE);
        insertTrie(temp,"<",__SYMBOL,__LESS);
        insertTrie(temp,"/",__SYMBOL,__DIV);
        insertTrie(temp,"*",__SYMBOL,__MULT);
        insertTrie(temp,"(",__SYMBOL,__LPARAN);
        insertTrie(temp,")",__SYMBOL,__RPARAN);
        insertTrie(temp,"[",__SYMBOL,__LCLOSED);
        insertTrie(temp,"]",__SYMBOL,__RCLOSED);
        insertTrie(temp,",",__SYMBOL,__COMMA);
        insertTrie(temp,"{",__SYMBOL,__LCURLY);
        insertTrie(temp,"}",__SYMBOL,__RCURLY);

    }



    return temp;
}

TrieNode * 
createNode()
{
    TrieNode * temp = malloc(sizeof(TrieNode));
    if(temp == NULL)
    {   
        perror("createNode:Couldn't Allocate Memory!\n");
        exit(74);
    }
    

    temp->type= __NONE;
    temp->val=0; 
    return temp;

}

//insert word into trie
int 
insertTrie(Trie * trie,char * str, TokenType type,unsigned char val)
{

    int len = strlen(str);

    TrieNode * curr = trie->head;

    for(int i=0; i< len ; i ++)
    {
        if((int)(str[i])>=128)
            return 0;
        if(curr->nodes[(int)str[i] ] == NULL)
        {
            curr->nodes[(int)str[i]] = createNode();
        }
            curr = curr->nodes[(int)str[i]];
    }

    curr->type = type;
    
    curr->val = val;

    trie->size++;

    return 1;
}

TokenType 
getType(Trie * trie,char * str)
{
     int len = strlen(str);

    TrieNode * curr = trie->head;

    for(int i=0; i< len ; i ++)
    {
        if(curr->nodes[str[i] ] == NULL)
        {
            return -1;
        }
        
            curr = curr->nodes[str[i]];
    }
    

    return curr->type;


}

int 
findTrie(Trie * trie,char * str)
{
     int len = strlen(str);

    TrieNode * curr = trie->head;

    for(int i=0; i< len ; i ++)
    {
        if(curr->nodes[str[i] ] == NULL)
        {
            return 0;
        }
        
            curr = curr->nodes[str[i]];
    }
    
    if(curr->type != __NONE)
        return curr->type;

    return 0;


}

int 
isAlpha(char * str)
{
    while(*str != '\0')
    {
        if(!(*str - 'a' >=0 && *str  <=25))
        {
            return 0;
        }
        str ++;
    }
    return 1;
}

int 
freeTrie(TrieNode* node)
{
    
    for(int i=0 ; i < 26;i++)
    {
        if(node->nodes[i]!=NULL)
        {
            freeTrie(node->nodes[i]);
        }
    }
    
    free(node);

    return 1;
}

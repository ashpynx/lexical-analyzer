#include "token.h"
#include "buffer.h"
#include "main.h"
#include "trie.h"



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
next_token( Trie * trie,Lexer * lex)
{
    

    //change with trie lookup for efficiency overall
    //discard next_word implementation for whitespace recognition 
    //if findTrie(curstring)==1 then look ahead for better match.if not, take it 
    //lets say nameint , n|ameint->na|meint->nam|eint->name|int -> __ID i|nt-> __ID in|t -> __ID __INT
    //how do we know when to cut? if we cant make up anything with the current string, if it can be id,
    //treat it as one , if we can make something up after some time with our current character,dont forget our first place
    //and look for matches in our current character.

    // |int x = 5;  i|nt in| int __INT __WHITESPACE  |x x __ID __WHITESPACE  |= =| __SYM __DECL __WHITESPACE |5 5| __VAL 5 __WHITESPACE |; ;| __SYM __SEMICOLON
    // (x % 2) 
    /*
     *  treenode node = tree.head
     *  while(curr!=EOF)
     *  {
     *      wtype lastw
     *      unsigned char lastval
     *      int back=0
     *      while((node[curr]!=NULL)
     *      {
     *          if node.type != __NONE
     *                 lastw = node.type
     *                 lastval=node.val
     *                 back=0
     *                 
     *          node = node[curr]
     *
     *          curr = nextletter
     *          back++
     *      }
     *      node = tree.head
     *      strcurr = strcurr - back
     *      if(id(currstr,back) || val(currstr,back))
     *          addtoken();     
     *      
     *      
     *            
     *  }
     *
     *
     *
     * */

    struct word nw = {.head = lex->curr,.length=0}; 
    TrieNode * node = trie->head;
        
    char curr = nw.head[nw.length++];
    
    while(curr!='\0' && (curr == ' ' || curr =='\n' || curr=='\t'))
    {
        if(curr=='\n')
        {
            lex->position=0;
            lex->line++;
            lex->curr += nw.length;
            nw.head+=nw.length;
            nw.length=0;
        }
        
        curr =nw.head[nw.length++];
    }
    if(curr=='\0')
    {
        lex->state = __EOF;
        return (Token){};
    }
    lex->curr+=nw.length-1;
    lex->position+=nw.length-1;
    nw.head+=nw.length-1;
    nw.length=0; 

    //
    //
    //
    //KEYWORDS && ID
    //
    //
    //
    //reject if number on first letter
    if(isalpha(curr) || curr=='_')
    {
        while (curr!='\0' && (isalpha(curr) || isdigit(curr) || curr=='_' ))
        {
             
            curr = nw.head[nw.length++];
            
        }
        if(curr=='\0')
        {   
            lex->state = __EOF;
        }
        lex->position += nw.length-1;
        lex->curr += nw.length-1;
        int val=is_keyword(trie,&((struct word){.head=nw.head,.length=nw.length-1}));
        if(val)
        {
            return (Token){.type = __KEYWORD,.val=val,.head=nw.head,.length=nw.length-1,.position=lex->position,.line = lex->line};

        }
        else 
        {
            return (Token){.type=__ID,.val=0,.head=nw.head,.length=nw.length-1,.position=lex->position,.line=lex->line};
        }

    }
    
    //
    //
    //
    //LVALUES
    //
    //
    //

    else if((curr>='0' && (curr <='9') || curr=='\'' || curr=='"'))
    {
        if(curr =='\'' || curr =='"')
        {
            char f = curr;
            nw.length++;
            curr = nw.head[nw.length++];
                while(curr!= '\0'&&curr!='\n'&&curr!=f) curr = nw.head[nw.length++];

            if(curr=='\0')
            {   
                lex->state = __EOF;
                lex->position+= nw.length;
                lex->curr+=nw.length;  
                return (Token){.type=__UNID};
            }
            if(curr=='\n')   
            {
                lex->line++;
                lex->position+= 0;
                lex->curr+=nw.length;  
                return (Token){.type=__UNID};
            }
            lex->position+= nw.length;
            lex->curr+=nw.length;  
            return (Token){.type = __LVALUE , .val =__VALSTRING,.head=nw.head,.length=nw.length,.position=lex->position,.line=lex->line};   

        }
        while (curr!='\0' && (isdigit(curr) || curr ==','))
        {
            curr = nw.head[nw.length++]; 
        }


        if(curr=='\0')
        {   
            lex->state = __EOF;
        }

        lex->position+= nw.length-1;
        lex->curr+=nw.length-1;
        int val = is_lvalue(&((struct word){.head=nw.head,.length=nw.length-1}));
        
        if(val)
        {
            return (Token){.type=__LVALUE,.val=val,.head=nw.head,.length=nw.length-1,.position=lex->position,.line=lex->line};
        }
        else 
        {
            return (Token){.type=__UNID,.head=nw.head,.length=nw.length-1,.position=lex->position,.line=lex->line};
        }

    }
    
    //
    //
    //
    //SYMBOLS
    //
    //
    //

    else 
    {

        int val=0;
        int len=0;
        int bestlen=0;
        while(curr!='\0' && !((curr ==' ' || curr=='\n' || curr=='\t') || ((curr >='a' &&curr<='z' )||(curr>='A' && curr <='Z') || curr=='_') || ((curr>='0' && curr <='9') || curr ==',' || curr=='\'' || curr == '"')))
        {
                

            if(node->nodes[curr]==NULL)
                break;

            node =node->nodes[curr];
            len++;

            if(node->val!=0)
            {
                bestlen=len;
                val=node->val;
            }

            curr=nw.head[nw.length++];

        }

        if (val!=0)
        {
            
            lex->position+=bestlen;
            lex->curr+=bestlen;

            return (Token){.type = __SYMBOL,.val=val,.head=nw.head,.length=bestlen,.position=lex->position,.line=lex->line};
            
        }
        else 
        {
            lex->position++;
            lex->curr++;
            return (Token){.type=__UNID,.head=nw.head,.length=1,.line=lex->line,.position=lex->position};
        }
    }


    return (Token){};







    /*int back=0;
        int lastval=0;

        while(curr!='\0' && !((curr ==' ' || curr=='\n' || curr=='\t') || ((curr >='a' &&curr<='z' )||(curr>='A' && curr <='Z') || curr=='_') || ((curr>='0' && curr <='9') || curr ==',' || curr=='\'' || curr == '"')))
        {
            back++;
            if((is_symbol(trie,&(struct word){.head = nw.head,.length=nw.length-1})))
                    {
                        back=0;
                    }
            curr = nw.head[nw.length++];
        }

    
        if(curr=='\0')
        {   
            lex->state = __EOF;
        }

        lex->position+=nw.length-1 ;
        lex->curr+=nw.length-1;
        int val = is_symbol(trie,&((struct word){.head=nw.head,.length=nw.length-1}));
        if(val)
        {
            return (Token){.type=__SYMBOL,.val=lastval,.head=nw.head,.length=nw.length-1,.position=lex->position,.line=lex->line};
        }
        else
        {
            return (Token){.type=__UNID,.head=nw.head,.length=nw.length-1,.position=lex->position,.line=lex->line};
        }
        */
       /*
        *
        *
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
        temp.length = nw.length;
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
    */
}

int
is_keyword(Trie * trie,struct word *w)
{
    TrieNode * curr = trie->head;
    for(int i=0 ; i  < w->length;i++)
    {
        if(curr->nodes[w->head[i]]==NULL)
            return 0;
        curr = curr->nodes[w->head[i]];
    }


    return curr->type == __KEYWORD? curr->val:0;
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
is_symbol(Trie * trie,struct word *w)
{
    TrieNode * curr = trie->head;
    for(int i=0; i< w->length;i++)
    {
        if(curr->nodes[w->head[i]]==NULL)
            return 0;
        curr = curr->nodes[w->head[i]];

    }

    return curr->type==__SYMBOL ? curr->val:0;
}

int 
is_identifier(struct word * w)
{
    struct word temp = *w;
    
    if(w->head[0] - '0' >=0 && w->head[0]-'0' <=9)
        return 0;


    for(int i=0; i < w->length; i++)
    {
        if( !( isalpha(w->head[i]) || ( w->head[i]>'0' && w->head[i]<'9' ) ) )   
            return 0;
    }
    
    return 1;
}

int
is_lvalue(struct word * w)
{
    int val=1;

    int comma=0;

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
        
        if(w->head[i] == ',' && i!=0 && comma==0)
        {
            comma=1;
            continue;
        }
        if(!(w->head[i] - '0' >= 0 && w->head[i] - '0' <=9))
        {
            val=0;

            break;
        }
    }
    
    //char support for later

    chr:

    
    return val;
}

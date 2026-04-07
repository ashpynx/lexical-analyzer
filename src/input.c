#include "input.h"
#include <ctype.h>


int
parse_inputfile(char * source,Trie * obj)
{


    int len =  strlen(source);
    char c =0;
    //find the first line where no blank line or # at start,copy the line into a buffer,
    //read the buffer and look for 3 words, if more, ignore.
    //such as
        
    /*

        # will skip this line
        int keyword 
        char keyword 1 

        inits int to 0,
        char to 1
        
        if char's value was 5, would continue from 5, not 1

       */
    char clearbuffer[1024] = { 0 };
    char buffer[1024] = { 0 };
    int line=1; 
    int i =0; 
    int topval=0; 
    char * linebuf[3] = { 0 };
    int skip=0; 
    while(i < len)
    {
        c = source[i];
        
        int oldpos=i>0?i-1:i;
        if(c=='#')
        {
            while (c!='\n')
            {
                c=source[i++];
            }
            continue;
        }
        //get line
        while(c!='\n')
        {
            c = source[i++];
        }
        line++;
        memcpy(buffer,source+oldpos,i-oldpos);
        
        //read as many words(3>=x>1) as possible
        //getword function,
        Token temp= { 0 };
        int len=0;
        for(int j = 0 ; j < 3;j++)
        {
            
            struct word curr = get_word(buffer+len);
            len += curr.length;
            linebuf[j]=curr.head;
            if(linebuf[j]==NULL)
            {
                if(j==2)
                    continue;
                else 
                {
                    if(j==1)
                    {
                        fprintf(stderr,"No Token Type found at line %d!\n",line);
                        skip=1;
                        break;
                    }
                    else 
                    {
                        //fprintf(stderr,"Nothing found at line %d...\n",line);
                        skip=1;
                        break;
                    }
                }
            }
        }
        //printf("\n");
        if(skip)
            goto free;
        //
        //
        //
        //insert into tree
        //
        //
        //

        //type specilization
        TokenType ty=0;
        if(linebuf[1]!=NULL)
        {
            if(strcmp(linebuf[1],"keyword")==0)
            {
                ty = __KEYWORD;
            }
            else if(strcmp(linebuf[1],"symbol")==0)
            {
                ty=__SYMBOL;
            }
            else 
            {
                fprintf(stderr,"TokenType string not recognized at line %d!\n",line);
                goto free;
            }
        }

        //val specilization

        
        int val=0;
        if(linebuf[2]==NULL)
            val = topval;
        else 
            val = atoi(linebuf[2]);

        if(val > topval)
        {
            topval = val;
        }
        else  
        {
            topval++;
            val = topval;
        }
        //printf("Inserting: |%s|,%d,%d\n",linebuf[0],ty,val);       
        //
        //
        //
        //
        insertTrie(obj,linebuf[0],ty,val);
        //
        //
        //
        //free here 
        //
        free: 
        for(int t = 0;t<3;t++)
            if(linebuf[t]!=NULL)
            {
                free(linebuf[t]);
                linebuf[t]=NULL;
            }
        //
        //clear the buffer
        memcpy(buffer,clearbuffer,1024);
        i++;
        skip=0;
    }


    return 1;

}

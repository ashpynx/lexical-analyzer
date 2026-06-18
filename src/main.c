#include <stdio.h>
#include "main.h"
#include "trie.h"
#include "buffer.h"
#include "token.h"
#include "input.h"
#include "file.h"
//todo
//
//interactive
//
//output name modes
//
//etc
//
//
//

atomic_int sigint =0;

void 
handler(int sig)
{
    sigint = 1;
}


int 
main(int argc
    ,char * argv[])
{
    signal(SIGINT,handler);
    if(argc <2)
    {
        fprintf(stderr,"Not Enough arguments!\n");
        print_help();
        return 0;
    }
    int hflag = strcmp(argv[1] , "-h"); 
    if(!hflag)
    {
        print_help();
        return 0;
    }

    Trie *obj; 
    int flaginp = strcmp(argv[1],"-i");
    if(flaginp)
    {
        fprintf(stderr,"-i option not found.fallback to defaults.-h for more info.\n");
        obj=initTrie(1);
    }

//actual source file logic here
//
    else {

        if(argv[2] == NULL)
        {
            perror("Source File Not found!\n");
            return 0;
        }

        obj=initTrie(0);
        char * source = read_file(argv[2]);
        parse_inputfile(source,obj);
        free(source);
        if(sigint) 
            goto free;

    }

    //if binary or readable?
    int bin=0;
    int sf=0;
    char buf[256] = {0};
    printf("Save into file?(y/n) ");
    fgets(buf,255,stdin);
    if(buf[0]=='y' || buf[0] == 'Y')
    {
        sf=1;
        printf("Save as binary?(y/n) ");
        fgets(buf,255,stdin);
        if(buf[0]=='y')
            bin=1; 
    }

    int startpoint = flaginp?1:3;
    
    char filename[256]= {0};

    for(int i=startpoint;i<argc;i++)
    {
        if(sigint)
            break;
        char * buffer;

        buffer = read_file(argv[i]);
    
        Lexer * lex = init_lexer(buffer);
        
        TokenArray * tokarr = init_tokenarray();
        
        Token temp;
        while(1)
        {
            temp = next_token(obj,lex);
            if(lex->state == __EOF)
            {
                break;
            }
            
            tokarr = push_token(tokarr,temp);
        }

        
        file * f; 

        if(sf)
        {
            
            f = malloc(sizeof(file));



            snprintf(filename,255,"lexer_output_%s.%s",argv[i],bin?"bin":"txt");

            f->fptr = bin?fopen(filename,"wb"):fopen(filename,"w");
            
            f->bin=bin;

        }
        
        printf("\nFile: %s\n\n",argv[i]);
        
        file out;

        out.fptr=stdout;
        out.bin=0;

        file_push(&out,tokarr);
        if(f)
        {
            file_push(f,tokarr);
            printf("\nSaved into %s\n",filename);
            
            fclose(f->fptr);
            free(f);
        }
        if(buffer)
            free(buffer);
        if(lex)
            free(lex);
        lex=NULL;
        if(tokarr)
        {
            free(tokarr->arr);
            free(tokarr);
        }
    }
    free:
    if(obj)
    {
        freeTrie(obj->head);
        free(obj);
    }
   return 0;
}   


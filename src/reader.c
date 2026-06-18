#include "main.h"
#include "token.h"
#include "file.h"

int
main(int argc, char * argv[])
{
    
    if(argc!=2)
        return 0;

    Token temp;

    file * f = malloc(sizeof(file));
        
    if(f==NULL)
        return 0;
    f->bin=0;

    f->fptr = fopen(argv[1],"rb");
    if(f->fptr==NULL)
    {   
        free(f);
        return 0;
    }
    size_t ofset = offsetof(Token,head);
    printf("\n");
    while(fread(&temp,ofset,1,f->fptr)==1)
    {
            
        temp.head = calloc(sizeof(char)*temp.length,1);

        if(temp.head==NULL)
        {
            printf("Cannot read token!\n");
            return 0;
        }

        if(fread((char*)temp.head,1,temp.length,f->fptr)!= temp.length)
        {
            free((char*)temp.head);
            break;
        }
        print_token(stdout,&temp);


        free((char*)temp.head);

    }
    printf("\n"); 
    fclose(f->fptr);

    free(f);

}


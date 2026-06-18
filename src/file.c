#include "file.h"



//function for printing into file



void 
file_push(file * f, TokenArray * arr)

{
    
    for(int i=0; i < arr->length; i++)
    {
        

        //binary logic
        //
        //we assume file is open as binary
        //
        //
        /*
       
        typedef struct 
        {

            TokenType type;

            unsigned char val;

            int position;
            
            int line;

            int length;

            const char * head;

   


        }Token;
         
         
         */

        //if we write the string, size is dynamic
        if(f->bin)
        {
            size_t offset_of_head = offsetof(Token,head);

            //write type , val , lenght in order
            //
            fwrite((arr->arr +i), offset_of_head,1,f->fptr);


            fwrite((arr->arr+i)->head,sizeof(char),arr->arr[i].length,f->fptr);

        }
        else 
        {

            print_token(f->fptr,arr->arr+i);

        }

    }
    


}




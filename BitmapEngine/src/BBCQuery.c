#include <stdio.h>
#include <stdlib.h>
#include "Core.h"
#include "ActiveRun.h"

int OR_BBC(byte * ret, byte * col1, unsigned int size1, byte * col2, unsigned int size2)
{


   


    
    //The header position in col1 of run1
    int pos1 = 0;

    //The header position in col2 of run2
    int pos2 = 0;

    //the position we are in in our output array
    int out_pos = 0;

    //The first active run
    activeRun *run1;
    run1 = initActiveRun(col1, size1, pos1);
    pos1++;

    //The second active run
    activeRun *run2;
    run2 = initActiveRun(col2, size2, pos2);
    pos2++;

    printf("run1->fill_len: %u\n", run1->fill_len);
    printf("run1->tail_len: %u\n", run1->tail_len);
    printf("run2->fill_len: %u\n", run2->fill_len);
    printf("run2->tail_len: %u\n", run2->tail_len);

    int k = 0;
    while(pos1 < size1 && pos2 < size2)
    {
        printf("pos1: %d\n", pos1);
        printf("pos2: %d\n", pos2);
        //If run1 is empty than initiate the next run from col1
        if(run1->tail_len == 0 && run1->fill_len == 0)
        {
            run1 = initActiveRun(col1, size1, pos1);
            pos1++;
        }
        //If run2 is empty thatn intiate the next run form col2
        if(run2->tail_len == 0 && run2->fill_len == 0)
        {
            run2 = initActiveRun(col2, size2, pos2);
            pos2++;
        }
        //While run1 and run2 are not empty keep operating
        while((run1->tail_len != 0 || run1->fill_len != 0) && (run2->tail_len != 0 || run2->fill_len != 0))
        {
            //fill OR fill
            if(run1->fill_len > 0 && run2->fill_len > 0){
            
                int lookAhead = 0;
                if(run1->fill_len > run2->fill_len)
                {
                    lookAhead = run2->fill_len;
                }
                else
                {
                    lookAhead = run1->fill_len;
                }

                printf("lookAhead: %d\n", lookAhead);

                int i;
                //0 fill OR 0 fill
                if(run1->fill_bit == 0 && run2->fill_bit == 0){
                   

                    
                    for(i = 0; i < lookAhead; i++)
                    {
                        //ERROR here, need to mallloc the *ret variable to the size
                        //of the column(s) we are compressing. This should be done 
                        //a tthe top of this file. 
                        ret[out_pos + i] = 0b00000000;
                    }
                }
                //1 fill OR 0 fill, as well as 1 fill OR 1 fill
                else
                {
                    for(i = 0; i < lookAhead; i++)
                    {
                        ret[out_pos + i] = 0b11111111;
                    }
                }
                out_pos += i;
                pos1 += i;
                pos2 += i;
                run1->fill_len -= lookAhead;
                run2->fill_len -= lookAhead;
                printf("run1->fill_len: %u\n", run1->fill_len);
                printf("run1->tail_len: %u\n", run1->tail_len);
                printf("run2->fill_len: %u\n", run2->fill_len);
                printf("run2->tail_len: %u\n", run2->tail_len);

            }
            //fill OR messy
            else if(run1->fill_len > 0 && run2->fill_len == 0){
                //0 fill and messy
                if(run1->fill_bit == 0){
                    ret[out_pos] = 0b00000000 | run2->tail_store[pos2];                 
                }
                //1 fill and messy
                else{
                    ret[out_pos] = 0b11111111 | run2->tail_store[pos2];
                }
                out_pos++;
                pos1++;
                pos2++;
                run1->fill_len--;
                run2->tail_len--;
            }
            //messy OR fill
            else if(run2->fill_len > 0 && run1->fill_len == 0){

                //0 fill and messy
                if(run1->fill_bit == 0){
                    ret[out_pos] = 0b00000000 | run1->tail_store[pos1];                 
                }
                //1 fill and messy
                else{
                    ret[out_pos] = 0b11111111 | run1->tail_store[pos1];
                }
                out_pos++;
                pos1++;
                pos2++;
                run2->fill_len--;
                run1->tail_len--;
            }
            //messy OR messy
            else{

                ret[out_pos] = run1->tail_store[pos1] | run2->tail_store[pos2];
                out_pos++;
                pos1++;
                pos2++;
                run1->tail_len--;
                run2->tail_len--;
            }
            printf("run1->fill_len: %u\n", run1->fill_len);
            printf("run1->tail_len: %u\n", run1->tail_len);
            printf("run2->fill_len: %u\n", run2->fill_len);
            printf("run2->tail_len: %u\n", run2->tail_len);


            /*printf("out_pos: %d\n", out_pos);
            printf("size1: %d\n", size1);
            printf("size2: %d\n", size2);
            printf("pos1: %d\n", pos1);
            printf("pos2: %d\n", pos2);
            printf("run1->fill_len: %u\n", run1->fill_len);
            printf("run2->fill_len: %u\n", run2->fill_len);
            printf("run1->tail_len: %u\n", run1->tail_len);
            printf("run2->tail_len: %u\n", run2->tail_len);*/

        }

        //If run1 is empty than update pos1 to the header postion of the next run
        printf("before free 1\n");
        if(run1->tail_len == 0 && run1->fill_len == 0)
        {
            printf("about to free run1\n");
            free(run1);
            printf("run1 is freed\n");
        }
        
        //If run2 is empty than update pos2 to the header positon of the next run

        printf("before free2\n");
        if(run2->tail_len == 0 && run2->fill_len == 0)
        {
            printf("about to free run2\n");
            free(run2);
            printf("run2 is freed\n");
        }
        
    //If on success than return 1
    }

    printf("about to return\n");
    return 1;
}

/*int AND_BBC(byte * ret, byte * col1, unsigned int size1, byte * col2, unsigned int size2)
{
    return 1;
}*/

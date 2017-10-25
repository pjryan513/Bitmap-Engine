    
#include <stdio.h>
#include <stdlib.h>
#include "Core.h"
#include "ActiveRun.h"

int OR_BBC(byte * ret, byte * col1, unsigned int size1, byte * col2, unsigned int size2)
{

    //The first active run
    activeRun *run1;

    //The second active run
    activeRun *run2;

    //The header position in col1 of run1
    int pos1;

    //The header position in col2 of run2
    int pos2;

    //the position we are in in our output array
    int out_pos;

    while(pos1 < size1 && pos2 < size2)
    {
        //If run1 is empty than initiate the next run from col1
        if(run1->tail_len == 0 && run1->fill_len == 0)
        {
            run1 = initActiveRun(col1, pos1);
        }

        //If run2 is empty thatn intiate the next run form col2
        if(run2->tail_len == 0 && run2->fill_len == 0)
        {
            run2 = initActiveRun(col2, pos2);
        }

        //While run1 and run2 are not empty keep operating
        while((run1->tail_len != 0 || run1->fill_len != 0) && (run2->tail_len != 0 || run2->fill_len != 0))
        {
            //suppose we aren't looking ahead. Then: 
            //ret[out_pos] = run1->
            //fill OR fill
            if(run1->fill_len > 0 && run2->fill_len > 0){
                //0 fill OR 0 fill
                if(run1->fill_bit == 0 && run2->fill_bit == 0){

                }
                //0 fill OR 1 fill
            }
            //fill OR messy
            else if(run1->fill_len > 0 && run2->fill_len = 0){
                //0 fill OR messy
                //1 fill OR 1 fill
                //1 fill OR messy
            }
            //vice versa
            else if(run2->fill_len > 0 && run1->fill_len = 0){
                //0 fill OR messy
                //1 fill OR 1 fill
                //1 fill OR messy
            }
            //messy OR messy
            else{
                //this should just be literal ORs of every byte
            }

        }

        //If run1 is empty than update pos1 to the header postion of the next run
        if(run1->tail_len == 0 && run1->fill_len == 0)
        {

            pos1 += run1->run_size;
            free(run1);
        }
        
        //If run2 is empty than update pos2 to the header positon of the next run
        if(run2->tail_len == 0 && run2->fill_len == 0)
        {

            pos2 += run2->run_size;
            free(run2);
        }
        

    //If on success than return 1
    return 1;
}

int AND_BBC(byte * ret, byte * col1, unsigned int size1, byte * col2, unsigned int size2)
{
    return 1;
}



bbcQuery(col_1, col_2, op){
    
    
    //below are some of the basic functions for bitwise operations we will be using. 
    //Hopefully somewhat self-explanatory

    BBCQuery(byte *col1, byte *col2, int op, size)



        if(op=='and')
            AndBBC()
        else if(op=='or')
            OrBBC()
    
    readHeader()
    readType1()
    readType2()
    readType3()
    readType4()


    AndBBC()
    char fillAndFill()
    char fillAndTail()
    char tailAndTail()

    OrBBC()
    //basic outline for the fillOrFill function. This is very much pseudo-code!
    char fillOrFill(){
        if(fill_bit1 == fill_bit2)
            if(fill_len1 <= fill_len2)
                toAdd = fill_len1*fill_bit1;
                result.add(toAdd);
            else
                toAdd = fill_len2*fill_bit1;
                result.add(toAdd);
        else if(fill_bit1 != fill_bit2)
            if(fill_len1 <= fill_len2)
                toAdd = fill_len1*1;
            else 
                toAdd = fill_len2*1;
            result.add(toAdd);
    }
    char fillOrTail()
    char tailOrTail()

}
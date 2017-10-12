    
#include <stdio.h>
#include <stdlib.h>
#include "Core.h"
#include "ActiveRun.h"

int OR_BBC(byte * ret, byte * col1, unsigned int size1, byte * col2, unsigned int size2)
{
    activeRun *run1;
    activeRun *run2;

    int pos1;
    int pos2;

    while(pos1 < size1 && pos2 < size2)
    {
        if(run1->tail_len == 0 && run1->fill_len == 0)
        {
            run1 = initActiveRun(col1, pos1);
        }

        if(run2->tail_len == 0 && run2->fill_len == 0)
        {
            run2 = initActiveRun(col2, pos2);
        }

        while((run1->tail_len != 0 || run1->fill_len != 0) && (run2->tail_len != 0 || run2->fill_len != 0))
        {
            
        }

        if(run1->tail_len == 0 && run1->fill_len == 0)
        {

            pos1 += run1->run_size;
        }
        
        if(run2->tail_len == 0 && run2->fill_len == 0)
        {

            pos2 += run2->run_size;
        }
    }

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
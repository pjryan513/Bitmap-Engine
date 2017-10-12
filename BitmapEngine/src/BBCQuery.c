    




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
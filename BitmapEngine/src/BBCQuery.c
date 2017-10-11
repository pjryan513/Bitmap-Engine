    




bbcQuery(col_1, col_2, op){
    //these are parameters to be used in our query engine. 
    //They keep track of various bytes, properties, headers, etc.
    char *col_1
    char *col_2
    curr_byte1
    curr_byte2
    curr_run1
    curr_run2

    //find smaller of these when comparing fills
    fill_len1
    fill_len2

    //if either tail length is 0, get the next header/run
    tail_len1
    tail_len2
    fill_bit1
    fill_bit2

    //in general, find the smaller of these, loop over this length
    run_size1
    run_size2
    odd_pos_1
    odd_pos_2
    
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
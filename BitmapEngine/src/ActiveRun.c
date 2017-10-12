//File for processing query bytes 


//determines the type of run we are looking at
int getHeadType(byte header){

	/*unsigned char h_type4 = header >> 4;
	unsigned char h_type3 = header >> 5;
	unsigned char h_type2 = header >> 6;
	unsigned char h_type1 = header >> 7;*/

	//it's a type 1 run 
	if(header >> 7){
		return 1;
	}
	//it's a type 2 run 
	else if(header >> 6){
		return 2;
	}
	//it's a type 3 run 
	else if(header >> 5){
		return 3;
	}
	//it's a type 4 run
	else if(header >> 4){
		return 4;
	}
}

/*
param: the current run in the form of an unsigned char *
return: the number of counter bytes in the run
*/
unsigned int counterBytes(byte * run){
	int pos = 1;
	unsigned int f_len; //keeping it unsigned? I think this helps
	do
	{
		unsigned int temp = run[pos] << 1;
		temp >>= 1;
		f_len = f_len + temp; //I believe we can add chars to ints
		pos++;
	}while(run[pos] >> 7 != 0);

	return f_len;
}


activeRun *initActiveRun(byte *run){
    activeRun *curr_run;

    //storing the run in the acitve run
    curr_run->run_seq = run;

    //finding the type for the run
    curr_run->run_type = getHeadType(run[0]);

    //if the type is 3 or 4 then counter bytes follow the header byte.
    //need to read the counter bytes
    if(curr_run->run_type == 1)
    {
    	//getting the fill_bit for type 1
    	byte bit_temp = run[0] << 1;
    	bit_temp >>=7;
    	curr_run->fill_bit = bit_temp;

    	//getting fill_len for type 1
    	byte fill_temp = run[0] << 2;
    	fill_temp >>= 6;
    	curr_run->fill_len = fill_temp;

    	//getting tail_len for type 1
    	byte tail_temp = run[0] << 4;
    	tail_temp >>= 4;
    	curr_run->tail_len = tail_temp;
    }
    else if(curr_run->run_type == 2)
    {
    	//getting the fill_bit for type 2
    	byte bit_temp = run[0] << 2;
    	bit_temp >>=7;
    	curr_run->fill_bit = bit_temp;

    	//getting fill_len for type 2
    	byte fill_temp = run[0] << 3;
    	fill_temp >>= 6;
    	curr_run->fill_len = fill_temp;

    	//getting odd_pos for type 1
    	byte odd_temp = run[0] << 5;
    	odd_temp >>= 5;
    	curr_run->odd_pos = odd_temp;

    }
    else if(curr_run->run_type == 3)
    {
    	//getting fill_bit for type 3
    	byte bit_temp = run[0] << 3;
    	bit_temp >>= 7;
    	curr_run->fill_bit = bit_temp;

    	//getting fill_len for type 3
        curr_run->fill_len = counterBytes(run);

     	//getting tail_len for type 3
    	byte tail_temp = run[0] << 4;
    	tail_temp >>= 4;
    	curr_run->tail_len = tail_temp;   
    }
    else if(curr_run->run_type == 4)
    {
    	//getting fill_bit for type 4
		byte bit_temp = run[0] << 4;
    	bit_temp >>= 7;
    	curr_run->fill_bit = bit_temp;

    	//getting fill_len for type 4
        curr_run->fill_len = counterBytes(run);

		//getting odd_pos for type 4
    	byte odd_temp = run[0] << 5;
    	odd_temp >>= 5;
    	curr_run->odd_pos = odd_temp;        
    }
    
    return curr_run;

}



void printActiveRun(activeRun * run)
{
	printf("The contents of the active run \n");
	printf("header: %c\n",run->header);
	printf("run type: %u\n", run->run_type);
	printf("fill bit: %u\n", run->fill_bit);
	printf("fill length: %u\n", run->fill_len);
	if(run->run_type == 1 || run->run_type == 3)
	{
		printf("tail length: %u\n", run->tail_len);
	}
	else if(run->run_type == 2 || run->run_type == 4)
	{
		printf("odd position: %u\n", run->odd_pos);
	}
}


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
	while(run[pos] >> 7 != 0)
	{
		pos++;
		f_len = f_len + run[pos]; //I believe we can add chars to ints
	}

	return f_len;
}

void readHeader(byte header, activeRun * curr_run)
{

}


activeRun *initActiveRun(byte *run){
    activeRun *curr_run;
    curr_byte->run_type = getHeadType(run[0]);
    if(run_type == 3 || run_type == 4){
        curr_byte->fill-len = counterBytes(run);
        byte *header_array;
    }

    readHeader(run, curr_run);
    return curr_run;

}



void printActiveRun(activeRun * run){

}


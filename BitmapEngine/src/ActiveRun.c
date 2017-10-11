//File for processing query bytes 


//determines the type of run we are looking at
int getHeadType(unsigned char header){

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


activeRun *initActiveRun(byte *col){
    int i;
    activeRun *curr_byte;
    curr_byte->run_type = readHeader(col1[i]);
    if(run_type == 3 || run_type == 4){
        int counters = counterBytes(col);
        byte *header_array;
    }
}



printActiveByte(){

}


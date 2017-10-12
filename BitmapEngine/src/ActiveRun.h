//defining the activeByte struct

#ifndef ACTIVEWORD_H_
#define ACTIVEWORD_H_

#include "Control.h"


typedef struct activeByte{
	byte header;
	unsigned int run_type;
	byte *run_seq;
	unsigned int tail_len; //only used for type 1 and 3
	unsigned int odd_pos;  //only used for type 2 and 4  
	unsigned int fill_bit;
	unsigned int fill_len;
}

int counterBytes(byte * run);

activeRun *initActiveRun(byte *run);

void printActiveRun();

void readHeader(byte header; activeRun * curr_run);

#endif /* ACTIVEWORD_H_ */
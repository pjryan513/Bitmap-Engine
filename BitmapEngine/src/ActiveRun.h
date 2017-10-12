//defining the activeByte struct

#ifndef ACTIVEWORD_H_
#define ACTIVEWORD_H_

#include "Control.h"


typedef struct activeRun{
	byte header;
	unsigned int run_type;
	byte *run_seq;
	unsigned int tail_len; //only used for type 1 and 3
	unsigned int odd_pos;  //only used for type 2 and 4  
	unsigned int fill_bit;
	unsigned int fill_len;
}activeRun;

int getHeadType(byte);

int counterBytes(byte *);

activeRun *initActiveRun(byte *);

void printActiveRun(activeRun *);

#endif /* ACTIVEWORD_H_ */
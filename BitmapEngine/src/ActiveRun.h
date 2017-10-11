//defining the activeByte struct

#ifndef ACTIVEWORD_H_
#define ACTIVEWORD_H_

#include "Control.h"


typedef struct activeByte{
	byte header;
	unsigned int run_type;
	byte *curr_run;
	unsigned int tail_len;
	unsigned int fill_bit;
	unsigned int fill_len;
}

int counterBytes(byte * run);

activeRun *initActiveRun(byte *run);

void printActiveRun();

#endif /* ACTIVEWORD_H_ */
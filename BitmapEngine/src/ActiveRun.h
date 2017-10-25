//defining the activeByte struct

#ifndef ACTIVEWORD_H_
#define ACTIVEWORD_H_

#include "Control.h"


typedef struct activeRun{
	
	//The header byte of the current run
	byte header;

	//The type of the run, can be 1, 2, 3 or 4
	unsigned int run_type;

	//Pointer to the compressed sequnce of bytes
	byte *run_seq;
	byte *full_seq;

	//The length of the tail in bytes
	unsigned int tail_len; //only used for type 1 and 3, if of type 2 or 4 then value will always be 1 (note in this case there is no physical tail but a logical tail of 1)

	//The location of the odd bit in the current run
	unsigned int odd_pos;  //only used for type 2 and 4 (!!! will be non-initalized if type 1 or 3 !!!) 

	//The fill bit corresponds to the bit being stored in the fill, storing a 1 means a 1-fill, stroing a 0 means a 0-fill
	unsigned int fill_bit;

	//The length of the fill in bytes
	unsigned int fill_len; 	

	//the position of  the run starting at the header.  Based off the over all compressed bit sequence.
	int run_pos;	

	//the poisiton of the tail bytes based from run_pos.	
	int tail_pos;

	//how many bytes are in the run			
	unsigned int run_size;	

	//The literal tail bytes of the current run, (!!! will be non-initalized if type 2 or 4 !!!)
	byte *tail_store;
}activeRun;

int getHeadType(byte);

int counterBytes(byte *);

activeRun *initActiveRun(byte *);

void printActiveRun(activeRun *);

#endif /* ACTIVEWORD_H_ */
/*///////////////////////////////////////////////////////////////////////////////
This file is used to perfrom utility functionality for the BBEC and BBCv2 files//
*////////////////////////////////////////////////////////////////////////////////


#ifndef UTIL
#define UTIL

#include "Core.h"

#define ZERO_BYTE 0
#define ONE_BYTE 1
#define ZERO_ODD_BYTE 2
#define ONE_ODD_BYTE 3
#define MESS_BYTE 4

#define TYPE_1 0
#define TYPE_2 1
#define TYPE_3 2
#define TYPE_4 3
#define TYPE_5 4

#define ZERO_BIT 0
#define ONE_BIT 1

#define FILL_LIMIT 3 //maybe????
#define TAIL_LIMIT 15 //maybe could be 16
#define TAIL_LIMIT_TYPE_4 8
#define TAIL_LIMIT_FIVE 3
#define FILL_LIMIT_TYPE_3 127

#define FULL_FILL 255

#define TYPE_1_HEADER 128
#define TYPE_2_HEADER 64
#define TYPE_3_HEADER 32
#define TYPE_4_HEADER 16 
#define TYPE_5_HEADER 0

#define NEWRUN 0
#define ACTIVE_RUN 1

typedef unsigned char byte;

typedef struct compressResult {
	unsigned char *compressed_seq;
	int size;
} compressResult;

typedef struct runData {
	//This is the size of the uncompressed block of bytes
	unsigned int size;

	//This is the array of bytes that are to be compressed
	unsigned char *toCompress;

	//This is the length (number of) fills in the current run we are compressing
	//A fill is either an entire byte of all zeros or all ones
	unsigned int fill_len;

	//This is the length (number of) tails in the current run we are compressing
	//A tail is a byte that can not be compressed because it is not all zeros or ones Ex: 00101000
	unsigned int tail_len;

	//This is the type of the run we are currently compressing
	//0: we are of type 1 
	//1: we are of type 2
	//2: we are of type 3
	//3: we are of type 4
	//the type of the run can be changed during the compressing
	unsigned int run_type;

	unsigned int odd_pos;

	//The fill_bit is the type of fill we are compressing, can either be 0 or 1
	//Is determined by the first 0 or 1 fill we encounter
	byte fill_bit;

	//If reading uncompressed bytes form a file, this will be the pointer to the file
	FILE *colFile;

	//The next_byte to look at in the uncompressed sequence
	byte next_byte;

	//The type of the byte we are trying to compress
	//The type of type we are dealing with determines what actions the current run will take
	//EX: store it, change run_type or start a new run
	unsigned int byte_type;

	//the fill bit type of the current byte to compress, used for comparision.
	unsigned int comp_fill_bit;

	byte *tail_store;

	//Pointer to the struture that keeps track of the output information for the compression algorithm.
	//This structure is what will be returned at the end of the algorithm
	compressResult * compress;

	//byte *compressBytes; //the current block of uncompressed bytes
	//struct blockBytes *nextBlock; //the next block of bytes to compress
} runData; 

int findOddPos(byte oddByte, unsigned int fill_bit);

compressResult * fillStore(unsigned int fill_len, byte fill_bit);

void addCompressSeq(runData *param, byte toAdd);

void getByteTypes(runData *param);

void printRunData(runData *param);

void printCompressData(compressResult *param);

#endif
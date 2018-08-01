//BBCCompressor.h

#ifndef BBEC
#define BBEC
/*#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>

#include "util.h"*/
#include "Core.h"

typedef struct baseExpo {
	int base;
	int expo;
} baseExpo;

baseExpo * expoDecomp(int num);

int updateRunEx(runData *param);

int endRunEx(runData *param);

void storeCompressEx(runData *param);

void startNewRunEx(runData *param);

compressResult * bbecRun(byte *to_compress, int size);

void compressUsingBBEC(struct blockSeg * param);

#endif
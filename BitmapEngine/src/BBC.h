//BBCCompressor.h

#ifndef BBC
#define BBC
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

int updateRun(runData *param);

int endRun(runData *param);

void storeCompress(runData *param);

void newRun(runData *param);

compressResult * bbcRun(byte * to_compress, int size);

void compressUsingBBCv2(struct blockSeg * param);

#endif

/*///////////////////////////////////////////////////////////////////////////////
This file is used to perfrom utility functionality for the BBEC and BBCv2 files//
*////////////////////////////////////////////////////////////////////////////////


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

//gets the type of a RAW byte
void getByteTypes(runData *param){
  byte b = param->next_byte;
  if(param->next_byte == 0){
    param->byte_type = ZERO_BYTE;
    param->comp_fill_bit = 0;
  }
  else if(param->next_byte == 255){
    param->byte_type = ONE_BYTE;
    param->comp_fill_bit = 1;
  }
  //if fill bit == 0, then we can use the ODD OBE BYTE. if the fill bit == 1, then we can use the ODD ZERO BYTE.
  //what if we are starting a new run? (NO FILL BIT DEFINED YET).
  //then we can attach either type of ODD BYTE to the end of a 1-bit-long type 2 run, and adjust the fill bit accordingly.
  //checks to see if there is
  //if(param->fill_bit == 0){
  else if(b == 1 || b == 2 || b == 4 || b == 8 || b == 16 || b == 32 || b == 64 || b == 128){
    param->byte_type =  ZERO_ODD_BYTE;
    param->comp_fill_bit = 0;
  }
  //}
  else if(b == 254 || b == 253 || b == 251 || b ==247 || b ==239 || b ==223 || b == 191 || b == 127){
    param->byte_type = ONE_ODD_BYTE;
    param->comp_fill_bit = 1;
  }

  else{
    param->byte_type = MESS_BYTE;
    param->comp_fill_bit = 0; //just being filled to pretty any unsee null errors, should go unused
  }
}

int findOddPos(byte oddByte, unsigned int fill_bit)
{
  int i;
  int expo = 1;
  for(i = 0; i < 8; i++)
  {
    if(oddByte == expo || oddByte == (255 - expo))
    {
      return i;
    }

     expo = expo *2;
  }
  return -1;
}

compressResult * fillStore(unsigned int fill_len, byte fill_bit)
{
  int i = 0;
  byte * fill = malloc(sizeof(byte*));
  while(fill_len > FILL_LIMIT_TYPE_3)
  {
    fill = realloc(fill, sizeof(byte *) * (i +1));
    fill[i] = FULL_FILL;

    fill_len -= FILL_LIMIT_TYPE_3; //Even though FULL_FILL is 255 we subtract 127 because only 7-bits are used for storage FSB is used to tell if more fill storage follows
    i++;
  }

  if(fill_len > 0)
  {
    fill = realloc(fill, sizeof(byte*) * (i+1));
    fill[i] = fill_len;
    i++;
  }

  compressResult * fill_done = (compressResult *) malloc(sizeof(compressResult *));
  fill_done->compressed_seq = fill;
  fill_done->size = i;
  return fill_done;
}

void addCompressSeq(runData *param, byte toAdd)
{
  param->compress->compressed_seq = realloc(param->compress->compressed_seq, sizeof(byte*) * (param->compress->size + 1));
  param->compress->compressed_seq[param->compress->size] = toAdd; //the reason we can use param->compress->size as the index is because it is not updated till after we store the current data
  param->compress->size++;
}

void printRunData(runData *param)
{
  printf("PRINT RUN DATA: \n");
  printf("fill_len is: %u\n", param->fill_len);
  printf("tail_len is: %u\n", param->tail_len);
  printf("fill_bit is: %u\n", param->fill_bit);
  printf("next_byte is: %u\n", param->next_byte);
  printf("comp_fill_bit is: %u\n", param->comp_fill_bit);
  printf("run_type is: %u\n", param->run_type);
  printf("byte_type is: %u\n", param->byte_type);

  int i;

  printf("tail store is: [");
  for(i = 0; i < param->tail_len; i++)
  {
    printf("%u",param->tail_store[i]);
    if(i < param->tail_len-1)
    {
      printf(", ");
    }
  }
  printf("]\n");
}

void printCompressData(compressResult *param)
{
  printf("compressed sequence: [");

  int i;
  for(i = 0; i < param->size; i++)
  {
    printf("%u",param->compressed_seq[i]);
    if(i < param->size-1)
    {
      printf(", ");
    }
  }
  printf("]\n");
}
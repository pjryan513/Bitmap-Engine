/*#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>

#include "BBEC.h"
#include "util.h"*/
#include "BBEC.h"
#include "Core.h"

//////////////////////////////////////////////////
//              helper function                 //
//////////////////////////////////////////////////



int updateRunEx(runData *param)
{
  if(param->run_type == TYPE_1)
  {
    if(param->fill_len > 3)
    {
      param->run_type = TYPE_3;
      return 0;
    }
    else if(param->byte_type == ONE_ODD_BYTE || param->byte_type == ZERO_ODD_BYTE)
    {
      param->run_type = TYPE_2;
      param->odd_pos = findOddPos(param->next_byte, param->fill_bit);
      return 0;
    }
  }
  else if(param->run_type == TYPE_3)
  {
    if(param->fill_len > FILL_LIMIT_TYPE_3)
    {
      param->run_type = TYPE_5;
      return 0;
    }
    else if(param->byte_type == ONE_ODD_BYTE || param->byte_type == ZERO_ODD_BYTE)
    {
      param->run_type = TYPE_4;
      param->odd_pos = findOddPos(param->next_byte, param->fill_bit);
      return 0;
    }
  }
  return 1;
}

void startNewRunEx(runData * param)
{
  param->fill_len = NEWRUN;
  param->tail_len = NEWRUN;

  int i;
  for(i = 0; i < TAIL_LIMIT; i++)
  {
    param->tail_store[i] = NEWRUN;  
  }

  param->fill_bit = 0;

  param->run_type = TYPE_1;
}

baseExpo * expoDecomp(int num)
{
  int x = num;
  int base = 1;
  int expo = 1;

  int i;
  for(i = 6; i > 1; i--)
  {
    int j = 1;
    while(pow(i,j) < x && j < 17)
    {
      j++;
    }
    j--; //we dec because we need to go until we are beyond x so take a step back and that is the closest value
    if(x-pow(i,j) < x-pow(base,expo))
    {
      base = i;
      expo = j;
    }
  }
  baseExpo *ret = (baseExpo*) malloc(sizeof(baseExpo));
  ret->base = base;
  ret->expo = expo;

  return ret;
}

void storeCompressEx(runData *param)
{
  if(param->run_type == TYPE_1)
  {
    //blank type 1 header
    byte header = TYPE_1_HEADER;

    //add fill bit
    byte temp = param->fill_bit;
    temp <<= 6;
    header |= temp;

    //add fill len
    temp = param->fill_len;
    temp <<= 4;
    header |= temp;

    //add tail len
    header |= param->tail_len;

    addCompressSeq(param, header);

    int i;
    for(i = 0; i < param->tail_len; i++)
    {
      addCompressSeq(param, param->tail_store[i]);
    }
  }
  else if(param->run_type == TYPE_2)
  {
    //blank type 2 header
    byte header = TYPE_2_HEADER;

    //add fill bit
    byte temp = param->fill_bit;
    temp <<= 5;
    header |= temp;

    //add fill len
    temp = param->fill_len;
    temp <<= 3;
    header |= temp;

    //add odd pos
    header |= param->odd_pos;

    addCompressSeq(param, header);
  }
  else if(param->run_type == TYPE_3)
  {
    //blank type 3 header
    byte header = TYPE_3_HEADER;

    //add fill bit
    byte temp = param->fill_bit;
    //001x | xxxx
    temp <<= 4;
    header |= temp;

    //add tail
    header |= param->tail_len;

    addCompressSeq(param, header);

    compressResult *three_fill = fillStore(param->fill_len, param->fill_bit);
    int i;
    for(i = 0; i < three_fill->size; i++)
    {
      addCompressSeq(param, three_fill->compressed_seq[i]);
    }
    free(three_fill->compressed_seq);
    free(three_fill);

    for(i = 0; i < param->tail_len; i++)
    {
      addCompressSeq(param, param->tail_store[i]);
    }
  }
  else if(param->run_type == TYPE_4)
  {
    byte header = TYPE_4_HEADER;

    byte temp = param->fill_bit;
    temp <<= 3;
    header |= temp;

    header |= param->odd_pos;

    addCompressSeq(param,header);

    compressResult *four_fill = fillStore(param->fill_len, param->fill_bit);
    int i;
    for(i = 0; i < four_fill->size; i++)
    {
      addCompressSeq(param, four_fill->compressed_seq[i]);
    }
    free(four_fill->compressed_seq);
    free(four_fill);
  }
  else if(param->run_type == TYPE_5)
  {
    int num = param->fill_len;

    byte header = TYPE_5_HEADER;

    int header_pos = param->compress->size;

    byte temp = param->fill_bit;
    temp <<= 3;
    header |= temp;
    header |= param->tail_len;

    addCompressSeq(param,header);

    int follow_fill = 0;
    while(num > 255)
    {

      int baExpo = 0;

      if(follow_fill > 0)
      {
        param->compress->compressed_seq[param->compress->size-1] |= 128;
        follow_fill = 0;
      }

      baseExpo * bE = expoDecomp(num);
      byte temp_boy = (((bE->base)-2) << 4);
      baExpo |= temp_boy;
        //we substract two because for our purpose having base below 2 is useless.
        //Example base is 5 but we can store it as 3 because we know that 0 and 1 spots are not needed
        // so 0 means 2, 1 means 3 ect ect
      temp_boy = ((bE->expo)-2);

      baExpo |= temp_boy;

      addCompressSeq(param, baExpo);

      num -= pow(bE->base,bE->expo);

      if((bE->base - 2) < 0 || (bE->expo -2) < 0)
      {
        printf("HOLD ON: base and/or expo below zero, NOT GOOD\n");
      }
      follow_fill++;
      free(bE);
    }

    if(num > 0)
    {
      param->compress->compressed_seq[header_pos] |= 4;
      addCompressSeq(param, num);
    }

    int i;
    for(i = 0; i < param->tail_len; i++)
    {
      addCompressSeq(param, param->tail_store[i]);
    }
  }
}

int endRunEx(runData *param)
{
  if(param->run_type == TYPE_2 || param->run_type == TYPE_4)
  {
    storeCompressEx(param);

    //printf("---run is done--- \n");
    //printCompressData(param->compress);

    startNewRunEx(param);
    return 0;
  }
  else if(param->byte_type == ONE_BYTE || param->byte_type == ZERO_BYTE || param->byte_type == ZERO_ODD_BYTE || param->byte_type == ONE_ODD_BYTE)
  {
    if(param->comp_fill_bit != param->fill_bit)
    {
      storeCompressEx(param);

      //printf("---run is done---\n");
      //printCompressData(param->compress);

      startNewRunEx(param);
      return 0;
    }
    else if(param->tail_len > 0)
    {
      storeCompressEx(param);

      //printf("---run is done---\n");
      //printCompressData(param->compress);

      startNewRunEx(param);
      return 0;
    }
  }
  else if(param->run_type == TYPE_5 && param->tail_len >= TAIL_LIMIT_FIVE)
  {
    printf("tail len is %d\n", param->tail_len);
    storeCompressEx(param);

    startNewRunEx(param);
  }
  else if(param->tail_len > TAIL_LIMIT)
  {
    storeCompressEx(param);

    //printf("---run is done---\n");
    //printCompressData(param->compress);

    startNewRunEx(param);
    return 0;
  }
  return 1;
}


//////////////////////////////////////////////////
//                  main function               //
//////////////////////////////////////////////////


compressResult * bbecRun(byte * to_compress, int size){

  //these methods gather information from the header

  runData * param = (runData *) malloc(sizeof(runData));

  param->size = size;
  param->toCompress = to_compress;
  param->run_type = TYPE_1;

  param->tail_store = (byte *) malloc(sizeof(byte) * 15);

  param->compress = (compressResult *) malloc(sizeof(compressResult));
  param->compress->compressed_seq = (byte *) malloc(sizeof(byte));
  param->compress->size = 0;

  int i;

  //This array will hold the result of the compression algorithm
  //param->curr_run = (byte*) malloc(sizeof(byte)*size);
  
  //The size of curr_run array
  
  startNewRunEx(param);

  for(i = 0; i < param->size; i++)
  {
    //printf("starting bbccompress\n");
    //these functions should go in rawbitmapreader.c, for each column there should be a new file.
    //sprintf(compfile, "compressed_%d", i);
    //param->colFile = fopen("filewrite/compressed%d.txt", i, "w");
    
    param->next_byte = param->toCompress[i];//get the next byte from the block sequence of bytes

    getByteTypes(param);//get the type of next_byte: zero byte, one byte, odd byte ect ect

    if(i > 0)
    { //done for an end case that only can occur when i == 0
      endRunEx(param);
    }
    
    //If the run is new both fill and tail lens will be zero and we need to choose a new fill bit
    if(param->fill_len <= 0 && param->tail_len <= 0)
    {
      if(param->byte_type == ONE_BYTE || param->byte_type == ONE_ODD_BYTE)
      {
        param->fill_bit = 1;
      }
      else
      {
        param->fill_bit = 0;
      }
    }

    /*if(param->fill_bit == 0 && param->byte_type == ONE_ODD_BYTE)
    {
      param->byte_type = MESSY_BYTE;
    }
    else if(param->fill_bit == 1 && param->byte_type == ZERO_ODD_BYTE)
    {
      param->byte_type = MESSY_BYTE;
    }*/

    if(param->byte_type == ZERO_BYTE || param->byte_type == ONE_BYTE) //if we are a fill we need to increment fill_len
    {
      if(param->comp_fill_bit == param->fill_bit)
      {
        param->fill_len++;
      }
    }
    else if(param->byte_type == MESS_BYTE) //if we are a messy we need to increment tail_len
    {
      param->tail_store[param->tail_len] = param->next_byte;
      param->tail_len++;

    }
    updateRunEx(param);
    //printRunData(param);

  }

  storeCompressEx(param);

  //printf("size of compress run is %d:\n ", param->compress->size);

  compressResult * retResult = param->compress;

  free(param->tail_store);
  free(param);

  return retResult;
}

//////////////////////////////////////////////////////////////
/*Used to interface with the Bitmap-Engine research project //
  run by David Chiu of the University of Puget Sound        */
//////////////////////////////////////////////////////////////

void compressUsingBBEC(struct blockSeg * param){

  compressResult * result = bbecRun(param->toCompress, param->size); //compress the data

  //////////////////////////////////////////////////////////////////////////////////
  /*This part of the code is just for printing raw and compressed code for testing*/
  
  int printRaw = 0;
  int printComp = 0;
  int i;

  if(printRaw)
  {
    printf("\ntoCompress size: %d",param->size);
    printf("\ntoCompress: ");
    for(i = 0; i < param->size;i++)
    {
      printf("%d",(int)param->toCompress[i]);
      if(i < param->size-1)
      {
        printf(", ");
      }
    }
  }

  if(printComp)
  {
    printf("\ncompress size: %d",result->size);
    printf("\nCompressed: ");
    for(i = 0; i < result->size; i++)
    {
      printf("%d", (int)result->compressed_seq[i]);
      if(i<result->size-1)
      {
        printf(", ");
      }

    }
  }
  printf("\n");

  /////////////////////////////////////////////////////////////////////////////////

  fwrite(result->compressed_seq, 1, result->size, param->colFile); //write compressed data out
  fclose(param->colFile);

  //free remaining heaped data
  free(result->compressed_seq);
  free(result);
}

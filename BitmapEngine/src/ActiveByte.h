
#ifndef ACTIVEBYTE_H_
#define ACTIVEBYTE_H_

#include "Control.h"

typedef struct activeWord{
  int run_type; //the run type of the bbc compressed sequence.
  int fill_bit; //the fill bit of the bbc compressed sequence.
  int fill_length;  //the length of the fill bytes of the bbc compressed sequence
  int tail_length;  //the legnth of the tail bytes of the bbc compressed sequence

  char header;  //the original header for the bbc compressed sequence

}activeWord;

activeWord *initActiveByte(int);

activeWord *runType(char);




#endif /* ACTIVEWORD_H_ */

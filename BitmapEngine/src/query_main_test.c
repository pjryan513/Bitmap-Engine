#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Core.h"

int main(int argc, char*argv[])
{
	byte *ret;

	byte *col1;

	int col1Size;

	byte *col2;

	int col2Size;

	int option = 0; //use hard coded or read file
	int optionZeroType = 0;

	if(!option)
	{
		if(optionZeroType == 0)
		{


			char test1[4];
			char test2[4];

			test1[0] = 0b10110000;
			test2[0] = 0b10110000;


			col1Size = 4;
			col2Size = 4;

			int i;

			for(i = 1; i < col1Size; i++)
			{
				test1[i] = 0;
				test2[i] = 0;
			}

			col1 = test1;
			col2 = test2;
		}
	}

	BBCQuery(ret, col1, col2Size, col2, col2Size);
}
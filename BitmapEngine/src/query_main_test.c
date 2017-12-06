#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Core.h"

int main(int argc, char*argv[])
{

	byte *ret = (byte*) malloc(sizeof(byte)*10000);

	byte *col1;

	unsigned int col1Size;

	byte *col2;

	unsigned int col2Size;

	int option = 0; //use hard coded or read file
	int option2 = 1;

	if(!option)
	{
		if(option2 == 0)
		{


			char test1[1];
			char test2[1];

			test1[0] = 0b10110000;
			test2[0] = 0b10110000;


			col1Size = 1;
			col2Size = 1;

			int i;

			/*for(i = 1; i < col1Size; i++)
			{
				test1[i] = 0;
				test2[i] = 0;
			}*/

			col1 = test1;
			col2 = test2;
		}
		else if(option2 == 1)
		{
			char test1[1];
			char test2[1];

			test1[0] = 0b11110000;
			test2[0] = 0b11110000;

			col1Size = 1;
			col2Size = 1;

			col1 = test1;
			col2 = test2;
		}
	}
	else
	{
		//read from file
		FILE *fl;
		fl =fopen("query_test.txt","r");

		fclose(fl);


	}
	
	int ret_size = OR_BBC(ret, col1, col1Size, col2, col2Size);
	printf("ret_size %u\n", ret_size);
	int i;
	printf("Result of query: \n");
	for(i = 0; i < ret_size; i++)
	{
		printf("%u", ret[i]);
		if(i < ret_size -1)
		{
			printf(", ");
		}
		
	}
	printf("\n");
	free(ret);

}
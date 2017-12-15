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
	int option2 = 0;

	if(!option)
	{
		if(option2 == 0)
		{


			byte test1[10];
			byte test2[10];

			test1[0] = 0b10111001;
			test2[0] = 0b11111001;


			col1Size = 10;
			col2Size = 10;

			int i;

			test1[1] = 0b10101011;
			test2[1] = 0b11010101;


			test1[2] = 0b00111010;
			test2[2] = 0b10110000;

			//
			test1[3] = 0b01110111;
			test2[3] = 0b10011010;

			test1[4] = 0b11001100;
			test2[4] = 0b00011011;

			test1[5] = 0b01000101;
			test2[5] = 0b10110101;

			test1[6] = 0b10101110;
			test2[6] = 0b11110111;

			test1[7] = 0b10010101;
			test2[7] = 0b10100011;

			test1[8] = 0b10110111;
			test2[8] = 0b10000001;

			test1[9] = 0b11111111;
			test2[9] = 0b11111111;


			/*for(i = 1; i < col1Size; i++)
			{
				test1[i] = 0;
				test2[i] = 0;
			}*/

			col1 = test1;
			col2 = test2;

			printf("%u\n",test1[0]);
			printf("%u\n", test1[1]);
			printf("OR of spot 1's is: %u\n", (test1[1] | test2[1]));
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
		else if(option2 == 2)
		{
			char test1[11];
			char test2[11];

			test1[0] = 0b11110000;
			test2[0] = 0b11110000;

			test1[1] = 0b10111001;
			test2[1] = 0b11111001;

			test1[2] = 0b10101011;
			test2[2] = 0b11010101;

			test1[3] = 0b00111010;
			test2[3] = 0b10110000;

			test1[4] = 0b01110111;
			test2[4] = 0b10011010;

			test1[5] = 0b11001100;
			test2[5] = 0b00011011;

			test1[6] = 0b01000101;
			test2[6] = 0b10110101;

			test1[7] = 0b10101110;
			test2[7] = 0b11110111;

			test1[8] = 0b10010101;
			test2[8] = 0b10100011;

			test1[9] = 0b10110111;
			test2[9] = 0b10000001;

			test1[10] = 0b11111111;
			test2[10] = 0b11111111;



			col1Size = 11;
			col2Size = 11;

			col1 = test1;
			col2 = test2;
		}
		else if(option2 == 3)
		{
			char test1[1];
			char test2[2];

			test1[0] = 0b01110011;
			test2[0] = 0b11100001;

			test2[1] = 0b10010101;

			col1Size = 1;
			col2Size = 2;

			col1 = test1;
			col2 = test2;
		}

		else if(option2 == 4)
		{
			char test1[2];
			char test2[17];

			//run
			test1[0] = 0b00010000;
			test1[1] = 0b00010100;
			//test1[2] = 0b10101010;
			//test1[3] = 0b01000111;
			//test1[4] = 0b00100101;
			//test1[5] = 0b01101001;
			//test1[6] = 0b10010101;
			//test1[7] = 0b11101101;
			//test1[8] = 0b00010001;
			//test1[9] = 0b10010010;
			//test1[10] = 0b10101000;
			//test1[11] = 0b00011100;
			//test1[12] = 0b11001110;
			//test1[13] = 0b01101101;
			//test1[14] = 0b01101100;
			//test1[15] = 0b01101111;
			//test1[16] = 0b10010011;

			//run
			test2[0] = 0b01010111;

			//run
			test2[1] = 0b11110010;
			test2[2] = 0b10101101;
			test2[3] = 0b00111011;

			//run
			test2[4] = 0b10000101;
			test2[5] = 0b10101011;
			test2[6] = 0b11010101;
			test2[7] = 0b10000110;
			test2[8] = 0b00110000;
			test2[9] = 0b11101101;

			//run
			test2[10] = 0b10100110;
			test2[11] = 0b10010100;
			test2[12] = 0b10001110;
			test2[13] = 0b01110111;
			test2[14] = 0b10010100;
			test2[15] = 0b11111111;
			test2[16] = 0b11000001;
			

			col1Size = 2;
			col2Size = 17;

			col1 = test1;
			col2 = test2;
		}
		else if(option2 == 7){
			system("python binhextrans.py query_test_data1.txt bin 1");
			system("python binhextrans.py query_test_data2.txt bin 2");
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
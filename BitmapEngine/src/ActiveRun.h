//defining the activeByte struct

typedef struct activeByte{
	byte header;
	unsigned int run_type;
	byte *curr_run;
	unsigned int tail_len;
	unsigned int fill_bit;
	unsigned int fill_len;
}
# Bitmap Engine
### [github.io](https://alexander-io.github.io/Bitmap-Engine/)
Original code contribution by [aingerson](https://github.com/aingerson/Bitmap-Engine) as a research assistant under the direction of Professor D.Chiu.

## Linux Install & Execution instructions
```bash
# ensure Make, Java Developer Kit (JDK), and a C compiler are installed
# from terminal
git clone https://alexander-io.github.io/Bitmap-Engine/
cd Bitmap-Engine/BitmapEngine/src
make
# > javac WorkloadMain.java
# > java WorkloadMain
# > ls *.txt
# > bitmap_out_gc.txt  bitmap_out.txt  query_out.txt

cd ../../BitmapEngine/src/
make
# > gcc -Wall -c ActiveWord.c
# > gcc -Wall -c Clock.c
# > gcc -Wall -c Query.c
# > gcc -Wall -c QueryUtil.c
# > gcc -Wall -c RawBitmapReader.c
# > gcc -Wall -c SegUtil.c
# > gcc -Wall -c VALCompressor.c
# > gcc -Wall -c VALQuery.c
# > gcc -Wall -c WAHCompressor.c
# > gcc -Wall -c WAHQuery.c
# > gcc -Wall -c Writer.c
# > gcc -Wall -o main main.c ActiveWord.o Clock.o Query.o QueryUtil.o RawBitmapReader.o SegUtil.o VALCompressor.o VALQuery.o WAHCompressor.o WAHQuery.o Writer.o -lpthread -lm

make format
# > ./main F ../../BitmapWorkloadGenerator/src/bitmap_out.txt
# > formatting recognized

# > File: ../../BitmapWorkloadGenerator/src/bitmap_out.txt
# > 	UNSTRIPING BEGIN...COMPLETE
# > 	STRIPING(1/4) BEGIN...COMPLETE
# > 	STRIPING(2/4) BEGIN...COMPLETE
# > 	STRIPING(3/4) BEGIN...COMPLETE
# > 	STRIPING(4/4) BEGIN...COMPLETE
# > 	COMPLETE ALL

make compress_u
# ./main C ../../BitmapWorkloadGenerator/src/bitmap_out.txt 1 UNSTRIPED
# time: 0.003609...

make compress_s
# ./main C ../../BitmapWorkloadGenerator/src/bitmap_out.txt 1 STRIPED
# time: 0.005010...

# OUT OF SERVICE
make query_u

# OUT OF SERVICE
make query_s

```
Please note, query functionality is NOT working. For future programmers, there's a potentially problematic section in BitmapEngine/src/WAHQuery.c.

On line 93 there's this line :
  word_32 w1 = col1[c1++];

When issuing $ make query_u, a segmentation fault seems to occur at this line. This seems to be true because I've placed a print statement before and after, only the preceding printf() call makes it to standard out.

## References
  Research Article Title :
  Notes on Design and Implementation of Compressed Bit Vectors
  Authors : Kesheng Wu, Ekow J. Otoo, Arie Shoshani, Henrik Nordberg
  Date : September 27, 2001

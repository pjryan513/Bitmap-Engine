The src/ file in this present working directory contains a number of java files for the purpose of generating bitmap files. The following are a series of bash commands that can be used to generate the bitmap files. (make sure that you have JDK and make installed)
> $ cd src/
> $ make
> $ ls \*.txt
> bitmap_out_gc.txt  bitmap_out.txt  query_out.txt

Otherwise you can compile the java files directly by issuing
> $ cd src/
> $ javac WorkloadMain.java
> $ java WorkloadMain
> $ ls \*.txt
> bitmap_out_gc.txt  bitmap_out.txt  query_out.txt

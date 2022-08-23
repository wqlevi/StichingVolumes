gcc -Wall -I../include/ -fpic -O -c ../src/nifti1_io.c
gcc -Wall -I../include/ -fpic -O -c ../src/nifticdf.c
gcc -Wall -I../include/ -fpic -O -c ../src/nifti1_tool.c
gcc -Wall -I../include/ -fpic -O -c ../src/znzlib.c

gcc -shared -o libnifti1io.so nifti1_io.o znzlib.o nifti1_tool.o nifticdf.o 

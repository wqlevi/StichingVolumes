CC=gcc
<<<<<<< HEAD
CFLAGS=-O3 -pg -g
=======
CFLAGS=-Wall
>>>>>>> 3af7e1c54296598af2cd69a853a2cf3b1db9ba0a

all: stich

stich: assemble_3d.c
	$(CC) $(CFLAGS) assemble_3d.c  -o stich

time:
	time ./stich
niiio: nii_io.c
	$(CC) $(CFLAGS) -Iinclude -Llib nii_io.c -lniftiio -lm -o nii_io
clean:
<<<<<<< HEAD
	rm -f *.o stich *.csv *.txt *.dat
=======
	rm -f stich *.csv *.txt *.dat
>>>>>>> 3af7e1c54296598af2cd69a853a2cf3b1db9ba0a

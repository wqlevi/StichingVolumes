CC=gcc
CFLAGS=-Wall

all: stich

stich: assemble_3d.c
	$(CC) $(CFLAGS) assemble_3d.c  -o stich

time:
	time ./stich
niiio: nii_io.c
	$(CC) $(CFLAGS) -Iinclude -Llib nii_io.c -lniftiio -lm -o nii_io
clean:
	rm -f stich *.csv *.txt *.dat

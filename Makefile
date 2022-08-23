CC=gcc
CFLAGS=-O3 -pg -g
bins=stich nii_io

all: clean $(bins)

stich: assemble_3d.c
	$(CC) $(CFLAGS) assemble_3d.c  -o stich

time:
	time ./stich
nii_io: nii_io.c
	$(CC) $(CFLAGS) -Iinclude -Llib nii_io.c -lniftiio -lm -o nii_io
.PHONY: clean
clean:
	rm -f $(bins) *.o *.csv *.txt *.dat 

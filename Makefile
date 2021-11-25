CC=gcc
CFLAGS=-O3 -pg -g

all: stich

stich: assemble_3d.c
	$(CC) $(CFLAGS) assemble_3d.c  -o stich

time:
	time ./stich
clean:
	rm -f *.o stich *.csv *.txt *.dat
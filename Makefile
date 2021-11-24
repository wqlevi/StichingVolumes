CC=gcc
CFLAGS=

all: stich

stich: assemble_3d.c
	$(CC) $(CFLAGS) assemble_3d.c  -o stich

time:
	time ./stich
clean:
	rm -f stich *.csv *.txt *.dat
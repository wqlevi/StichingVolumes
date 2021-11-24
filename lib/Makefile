CC=gcc
SRCP=../src
SRC=$(wildcard $(SRCP)/*.c)
IDIR=../include
CFLAGS=-Wall -I$(IDIR) 
LDFLAGS=-shared 
DEPS=$($(IDIR)/*.h)
OBJS=$(SRC:.c=.o)

all: $(OBJS)
# sth. was lost here:
%.o: %.c 
	$(CC) $(CFLAGS) -fpic -O -c $(SRCP)/$^ 

ldmake: $(wildcard *.o)
	$(CC) $(LDFLAGS) -o libniftiio.so $^
#
.PHONY: clean
	rm -rf %.o
	echo clean done

libs: $(SRC)
	$(CC) $(CFLAGS) -fpic -O -c $(SRC) 

ldlib: $(wildcard *.o)
	$(CC) $(LDFLAGS) -o libniftiio.so $(wildcard *.o)


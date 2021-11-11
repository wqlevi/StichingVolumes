CC=gcc
SRCP=../src
SRC=$(wildcard $(SRCP)/*.c)
IDIR=../include
CFLAGS=-Wall -I$(IDIR) 
LDFLAGS=-shared 
DEPS=$($(IDIR)/*.h)
OBJS=$(SRC:.c=.o)

all: $(OBJS)

%.o: %.c 
	$(CC) $(CFLAGS) -fpic -O -c $(SRCP)/$^ 

ldmake: %.o
	$(CC) $(LDFLAGS) -o $^

.PHONY: clean
	rm -rf %.o
	echo clean done
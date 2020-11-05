DEBUG	= -g
CC	= gcc -c
LD	= gcc
CFLAGS	= $(DEBUG) -W -Wall
LIBS	=
LDFLAGS = $(DEBUG)

OBJS = process.o func.o

all : process

process  : $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

process.o : process.c addition.h
	$(CC) $(CFLAGS) $< -o $@

func.o : func.c addition.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) process

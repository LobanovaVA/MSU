DEBUG	= -g
CC	= g++ -c
LD	= g++
CFLAGS	= $(DEBUG) -W -Wall
LIBS	= -pthread -lpthread
LDFLAGS = $(DEBUG)

OBJS = main.o thread_func.o task.o

all : process

process  : $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

main.o : main_no_arr.cpp addition.h
	$(CC) $(CFLAGS) $< -o $@

thread_func.o : thread_func.cpp addition.h
	$(CC) $(CFLAGS) $< -o $@

task.o : task.cpp addition.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) *.out process

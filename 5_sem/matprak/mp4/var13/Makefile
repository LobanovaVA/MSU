# LIBS  = -lm -pthread -lpthread
# DEBUG = -g 

# CC = g++ -c
# LD = g++

# CFLAGS	= $(DEBUG) -W -Wall -Wextra -pedantic -Werror -O3
# LDFLAGS = $(DEBUG)


# all: a.out clean_obj

# a.out: $(patsubst %.cpp,%.o,$(wildcard *.cpp))
# 	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@ 

# %.o: %.cpp
# 	$(CC) $(CFLAGS) -MD $<

# include $(wildcard *.d)


# clean_obj:
# 	rm -f *.o *.d
	
# clean: clean_obj
# 	rm -f *.out 


DEBUG	= -g
CC	= g++ -c
LD	= g++
CFLAGS	= $(DEBUG) -W -Wall -Wextra -pedantic -Werror #-O3
LIBS	= -pthread -lpthread
LDFLAGS = $(DEBUG)

OBJS = main.o thread_func.o task.o time.o array.o

all : a.out 

a.out : $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

main.o : main.cpp addition.h
	$(CC) $(CFLAGS) $< -o $@

array.o : array.cpp addition.h
	$(CC) $(CFLAGS) $< -o $@	

thread_func.o : thread_func.cpp addition.h
	$(CC) $(CFLAGS) $< -o $@

task.o : task.cpp addition.h
	$(CC) $(CFLAGS) $< -o $@

time.o : time.cpp addition.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) *.out 
